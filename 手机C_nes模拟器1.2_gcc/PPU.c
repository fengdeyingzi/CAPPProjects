#include "nes_main.h"


/*�������� ------------------------------------------------------------------*/
/*�洢�����*/
uint8 NameTable[1024*2];

PPU_RegType PPU_Reg;
PPU_MemType PPU_Mem;

Spr_MemType	Spr_Mem;
SpriteType *sprite; //ָ���һ��sprite 0 ��λ��

/*��ʾ���*/
uint8 	SpriteHitFlag, PPU_Latch_Flag; //sprite #0 ��ʾ��ײ������ɨ���к�, ����λ�ƣ�2005д���־ 
int 	PPU_scanline;  					//��ǰɨ����
uint16	Buffer_scanline[8 + 256 + 8];	//����ʾ����,���±�Խ�����Ϊ7����ʾ�� 7 ~ 263  0~7 263~270 Ϊ��ֹ�����
uint8 PPU_BG_VScrlOrg, PPU_BG_HScrlOrg;
extern uint16 *LCDBUF;

/********************************************************************************
 **NES ��ɫ�� ��ɫ��RGB565�� 64
 */

const uint16 NES_Color_Palette[64] =
{
	0x73AE,0x20D1,0x0015,0x4013,0x880E,0xA802,0xA000,0x7840,
	0x4160,0x0220,0x0280,0x01E2,0x19EB,0x0000,0x0000,0x0000,
	0xBDF7,0x039D,0x21DD,0x801E,0xB817,0xE00B,0xD940,0xCA61,
	0x8B80,0x04A0,0x0540,0x0487,0x0411,0x0000,0x0000,0x0000,
	0xFFFF,0x3DFF,0x5CBF,0xA45F,0xF3DF,0xFBB6,0xFBAC,0xFCC7,
	0xF5E7,0x8682,0x4EE9,0x5FD3,0x075B,0x0000,0x0000,0x0000,
	0xFFFF,0xAF3F,0xC6BF,0xD65F,0xFE3F,0xFE3B,0xFDF6,0xFED5,
	0xFF34,0xE7F4,0xAF97,0xB7F9,0x9FFE,0x0000,0x0000,0x0000
};
/*
 **
 *********************************************************************************/


/*�������� ----------------------------------------------------------------------*/

/*
 * PPU ��ʼ��
 */
void PPU_Init(	uint8* patterntableptr,	/* Pattern table ��ַ*/
				uint8  ScreenMirrorType	/* ��Ļ��������*/
				)
{
	memset(&PPU_Mem, 0, sizeof(PPU_Mem));//����洢��
	memset(&Spr_Mem, 0, sizeof(Spr_Mem));
	memset(&PPU_Reg, 0, sizeof(PPU_Reg));
    sprite = (SpriteType  *)&Spr_Mem.spr_ram[0]; 
	PPU_Mem.patterntable0 =	 patterntableptr;
	PPU_Mem.patterntable1 =  patterntableptr + 0x1000;
	
	if(ScreenMirrorType == 0){  //ˮƽ����
		PPU_Mem.name_table[0] = &NameTable[0];
		PPU_Mem.name_table[1] = &NameTable[0];
		PPU_Mem.name_table[2] = &NameTable[1024];
		PPU_Mem.name_table[3] = &NameTable[1024];
	}else{						//��ֱ����
		PPU_Mem.name_table[0] = &NameTable[0];
		PPU_Mem.name_table[1] = &NameTable[1024];
		PPU_Mem.name_table[2] = &NameTable[0];
		PPU_Mem.name_table[3] = &NameTable[1024];
	}

	SpriteHitFlag = PPU_Latch_Flag = FALSE;
	PPU_BG_VScrlOrg = 0;
	PPU_BG_HScrlOrg = 0;
	PPU_scanline = 0;

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *  PPU �洢����Ĵ��������� 
 */

/*
 * ��PPU name table ����
 */
uint8 PPU_NameTablesRead(void)
{
	uint16 addrtemp = PPU_Mem.PPU_addrcnt & 0xFFF;

	if(addrtemp > 0xC00){
		return 	PPU_Mem.name_table[3][addrtemp - 0xC00];		//nametable3
	}
	if(addrtemp > 0x800){
	  	return 	PPU_Mem.name_table[2][addrtemp - 0x800];		//nametable2
	}
	if(addrtemp > 0x400){
	  	return 	PPU_Mem.name_table[1][addrtemp - 0x400];		//nametable1
	}else{
	  	return 	PPU_Mem.name_table[0][addrtemp];				//nametable0
	}
}

/*
 * дPPU name table ����
 */
void PPU_NameTablesWrite(uint8 value)
{
	uint16 addrtemp = PPU_Mem.PPU_addrcnt & 0xFFF;

	if(addrtemp > 0xC00){
		PPU_Mem.name_table[3][addrtemp - 0xC00] = value;		//nametable3
		return;
	}
	if(addrtemp > 0x800){
	  	PPU_Mem.name_table[2][addrtemp - 0x800] = value;		//nametable2
		return;
	}
	if(addrtemp > 0x400){
	  	PPU_Mem.name_table[1][addrtemp - 0x400] = value;		//nametable1
		return;
	}else{
	  	PPU_Mem.name_table[0][addrtemp] = value;				//nametable0
		return;
	}
}

/*
 * дPPU�洢��
 */
void PPU_MemWrite(uint8 value)
{
	switch(PPU_Mem.PPU_addrcnt & 0xF000){
	case 0x0000: //$0000 ~ $0FFF  ֻ�� - �뿨���й�
//		 PPU_Mem.patterntable0[PPU_Mem.PPU_addrcnt] = value;
		 break;
	case 0x1000: //$1000 ~ $1FFF  ֻ�� - �뿨���й�
//		 PPU_Mem.patterntable1[PPU_Mem.PPU_addrcnt & 0x0FFF] = value;
		 break;
	case 0x2000: //$2000 ~ $2FFF
		 PPU_NameTablesWrite(value);
		 break;
	case 0x3000: 
		 //$3000 ~ $3EFF	-- $2000 ~ $2EFF�ľ���
		 //$3F00 ~ $3F0F 	image  palette
		 //$3F10 ~ $3F1F	sprite palette
		 if((PPU_Mem.PPU_addrcnt & 0x1F) > 0x0F){
			PPU_Mem.sprite_palette[(PPU_Mem.PPU_addrcnt & 0xF)] = value;	//������ɫ����ֵ��
			if((PPU_Mem.PPU_addrcnt & 3) == 0){							//��Ӧλ��Ϊ͸��ɫ�ľ���
				PPU_Mem.sprite_palette[0] = PPU_Mem.image_palette[0] = value;
				PPU_Mem.sprite_palette[4] = PPU_Mem.image_palette[4] = value;
				PPU_Mem.sprite_palette[8] = PPU_Mem.image_palette[8] = value;
				PPU_Mem.sprite_palette[12] =PPU_Mem.image_palette[12]= value;
		 	}	
		 }else{
			PPU_Mem.image_palette[(PPU_Mem.PPU_addrcnt & 0xF)] = value; 	//������ɫ����ֵ��
		 }
		 break;
	}
	//��д�󣬵�ַ���������ӣ�����$2002 [bit2] 0��+1  1�� +32��
	PPU_Reg.R0 & PPU_ADDRINCR ? PPU_Mem.PPU_addrcnt += 32 : PPU_Mem.PPU_addrcnt++ ;
}

/*
 * ��PPU�洢��
 */
uint8 PPU_MemRead(void)
{
	//����Ӳ��ԭ��NES PPUÿ�ζ�ȡ���ص��ǻ���ֵ��Ϊʱ����ȡ��ַ��1��
	uint8 temp;

	temp = PPU_Mem.PPU_readtemp; //���滺��ֵ����Ϊ����ֵ
		
	switch(PPU_Mem.PPU_addrcnt & 0xF000){
	case 0x0000: //$0000 ~ $0FFF
		 PPU_Mem.PPU_readtemp = PPU_Mem.patterntable0[PPU_Mem.PPU_addrcnt];			 //��ȡ��ַָ��ֵ������
		 break;
	case 0x1000: //$1000 ~ $1FFF
		 PPU_Mem.PPU_readtemp = PPU_Mem.patterntable1[PPU_Mem.PPU_addrcnt & 0x0FFF]; //��ȡ��ַָ��ֵ������
		 break;
	case 0x2000: //$2000 ~ $2FFF
		 PPU_Mem.PPU_readtemp = PPU_NameTablesRead();								 //��ȡ��ַָ��ֵ������
		 break;
	case 0x3000: 
		 if(PPU_Mem.PPU_addrcnt >= 0x3F10){
		 	temp =  PPU_Mem.sprite_palette[(PPU_Mem.PPU_addrcnt & 0xF)];	//PPU ��ȡ���岻���� palette ��ɫ��,ֱ�ӷ���
		 	break; 	
	 	 }
		 if(PPU_Mem.PPU_addrcnt >= 0x3F00){
		 		temp = PPU_Mem.image_palette[(PPU_Mem.PPU_addrcnt & 0xF)];	//PPU ��ȡ���岻���� palette ��ɫ��,ֱ�ӷ���
		 		break;
		 }
		 break;
	default: temp = 0; 
	}
	//��д�󣬵�ַ���������ӣ�����$2002 [bit2] 0��+1  1�� +32��
	PPU_Reg.R0 & PPU_ADDRINCR ? PPU_Mem.PPU_addrcnt += 32 : PPU_Mem.PPU_addrcnt++ ;
	return temp;
}

/*
 * дPPU�Ĵ���
 */
void PPU_RegWrite(uint16 RX, uint8 value)
{

	switch(RX){
/*$2000*/
	case 0:	PPU_Reg.R0 = value;
/*$2001*/	break;
	case 1:	PPU_Reg.R1 = value;	 
/*$2003*/	break;
 	case 3: //Sprite Memory Address�� 8λ��ַ������
			Spr_Mem.spr_addrcnt = value;
/*$2004*/	break;
	case 4: //Sprite Memory Data ,ÿ�δ�ȡ sprite ram ��ַ������spr_addrcnt�Զ���1
			Spr_Mem.spr_ram[Spr_Mem.spr_addrcnt++] = value;
/*$2005*/	break;
	case 5:	//PPU_Reg.R5 = value;
			if(PPU_Latch_Flag){   //��1����ֱscroll����
				PPU_BG_VScrlOrg	= (value > 239) ? 0 : value;
		
			}else{				  //��0��ˮƽscroll����
				PPU_BG_HScrlOrg = value;
			}					 
			PPU_Latch_Flag ^= 1;
/*$2006*/	break;
	case 6:	

  		PPU_Mem.PPU_addrcnt = (PPU_Mem.PPU_addrcnt << 8) + value; //PPU �洢����ַ����������д��8λ����д��8λ
			PPU_Latch_Flag ^= 1;
/*$2007*/	break; 
	case 7:	/*д PPU Memory Data*/
			PPU_MemWrite(value);
			break;
	}
}

/*
 * ��PPU�Ĵ���
 */
uint8 PPU_RegRead(uint16 RX)
{
	uint8 temp;

	switch(RX){
	case 0: temp = PPU_Reg.R0;	//$2000 RW
			break;
	case 1: temp = PPU_Reg.R1;	//$2001 RW
			break;
	case 2: temp = PPU_Reg.R2;
			PPU_Reg.R2 &= ~(R0_VB_NMI_EN);
			PPU_Latch_Flag = 0;
		 	// Make a Nametable 0 in V-Blank
		    if ((PPU_scanline > 20 && PPU_scanline < 262) && !(PPU_Reg.R0 & R0_VB_NMI_EN)){
		      	PPU_Reg.R0 &= ~R0_NAME_TABLE;	 			//ѡ�� name table #0
		    }
			break;;	//$2002 R
	case 4:	/*�� Sprite Memory Data*/
			temp = Spr_Mem.spr_ram[Spr_Mem.spr_addrcnt++];
			break;
	case 7:	/*�� PPU Memory Data*/
			temp = PPU_MemRead();
			break;
	default :// printf("\r\nPPU ��ȡ��ַ���� %d", RX);
			return (uint8)RX;
	}

	return temp;	
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *  PPU ��ʾ������ 
 */

/*
 * ����sprite #0��ײ��־
 */
void NES_GetSpr0HitFlag(int y_axes)
{
	int16   i,y_scroll, dy_axes, dx_axes;
	uint8 y_TitleLine, x_TitleLine;
	uint8 spr_size, Spr0_Data, temp;
	uint8 nNameTable, BG_TitlePatNum;
	uint8 BG_Data0, BG_Data1, BG_Data;
	uint16 title_addr;
	uint8 *BG_Patterntable;
	uint8 *Spr_Patterntable;

	/*�ж�sprite #0 ��ʾ�����Ƿ��ڵ�ǰ��*/
	spr_size = PPU_Reg.R0 & R0_SPR_SIZE	? 0x0F : 0x07;		//spr_size 8��0~7��16: 0~15
	dy_axes = y_axes - (uint8)(sprite[0].y + 1);			//�ж�sprite#0 �Ƿ��ڵ�ǰ����ʾ��Χ��,0����ʵ��ֵΪFF
	if(dy_axes != (dy_axes & spr_size))			
		return;
	nNameTable = PPU_Reg.R0 & R0_NAME_TABLE;
	BG_Patterntable = PPU_Reg.R0 & BG_PATTERN_ADDR ? PPU_Mem.patterntable1 : PPU_Mem.patterntable0;//����pattern�׵�ַ
	y_scroll = y_axes + PPU_BG_VScrlOrg;  	//Scorll λ�ƺ󱳾���ʾ�е�Y���꣬����[00]��[01]��[10]��[11]��ÿ����ʾ(0+x_scroll_org,y_scroll_org)
	if(y_scroll > 255){
		y_scroll -= 256;
		nNameTable ^= NAME_TABLE_V_MASK; 		//��ֱ������Ļ���л�name table��
	}
    y_TitleLine = y_scroll >> 3; 				//title �к� 0~29��y�������8��
	x_TitleLine = (PPU_BG_HScrlOrg + sprite[0].x) >> 3;//title �к� 0~31��y�������8�� 
	dy_axes = y_scroll & 0x07;					//title��ʾy��ƫ������ ��8������
	dx_axes = PPU_BG_HScrlOrg & 0x07;		//title��ʾx��ƫ������ ��8������
	if(x_TitleLine > 31)					    //x�������ʾ
		nNameTable ^= NAME_TABLE_H_MASK;
	BG_TitlePatNum = PPU_Mem.name_table[nNameTable][(y_TitleLine << 5) + x_TitleLine]; 	//y_TitleLine * 32 +��x_TitleLine,��name����ȡ��sprite��ʾλ�õı�����title�ŵ� 
	BG_Data0  = BG_Patterntable[(BG_TitlePatNum << 4) + dy_axes];						//������ʾ����0
	BG_Data0 |= BG_Patterntable[(BG_TitlePatNum << 4) + dy_axes + 8];
	if((x_TitleLine + 1) > 31)					//x�������ʾ
		nNameTable ^= NAME_TABLE_H_MASK;
	BG_TitlePatNum = PPU_Mem.name_table[nNameTable][(y_TitleLine << 5) + x_TitleLine + 1]; //��name������һ��������ʾ��title�ŵ�
	BG_Data1  = BG_Patterntable[(BG_TitlePatNum << 4) + dy_axes];						//������ʾ����1
	BG_Data1 |= BG_Patterntable[(BG_TitlePatNum << 4) + dy_axes + 8];
	BG_Data = (BG_Data0 << dx_axes) | (BG_Data1 >> dx_axes);							//������Sprite #0 λ����ͬ�ĵ�ǰ��ʾ�е���ʾ����
	
	/*ȡ��sprite #0 ��ʾ����*/
	if(sprite[0].attr & SPR_VFLIP)							//����ֱ��ת
	 	dy_axes = spr_size - dy_axes; 						
	if(PPU_Reg.R2 & R0_SPR_SIZE){//8*16						//��Ϊ�棬sprite�Ĵ�С8*16
		/*ȡ������title Pattern�׵�ַ*/
		Spr_Patterntable = (sprite[0].t_num & 0x01) ? PPU_Mem.patterntable1 : PPU_Mem.patterntable0;
		title_addr = (sprite[0].t_num & 0XFE) << 4;		//*16,ԭ��ַ��*2
		Spr0_Data  = Spr_Patterntable[title_addr + dy_axes];
		Spr0_Data |= Spr_Patterntable[title_addr + dy_axes + 8];
	}else{						//8*8
		/*ȡ��sprite #0 ����title Pattern�׵�ַ*/
		Spr_Patterntable = (PPU_Reg.R0 & SPR_PATTERN_ADDR)	? PPU_Mem.patterntable1 : PPU_Mem.patterntable0;
		title_addr = sprite[0].t_num  << 4;				//*16
		Spr0_Data  = Spr_Patterntable[title_addr + dy_axes];
		Spr0_Data |= Spr_Patterntable[title_addr + dy_axes + 8];
	}

	if(sprite[0].attr & SPR_HFLIP){				/*��ˮƽ��ת, ��ת�ߵ�λ����*/
		temp = 0;
	   	for(i=0; i<8; i++){
	   		temp |= (Spr0_Data >> i) & 1;
			temp <<= i;
	   	}
		Spr0_Data = temp;
	}
	if(Spr0_Data & BG_Data){
		SpriteHitFlag = TRUE;
	} 
}

/*
 * ��ʾһ�б���������sprite��ײ��������ײ��־
 */
void NES_RenderBGLine(int y_axes)
{
	int 	i,y_scroll, /*x_scroll,*/ dy_axes, dx_axes;
	int    	Buffer_LineCnt, y_TitleLine, x_TitleLine;
	uint8 	H_byte, L_byte, BG_color_num, BG_attr_value;
	uint8 	nNameTable, BG_TitlePatNum;
	uint8  *BG_Patterntable;
	nNameTable = PPU_Reg.R0 & R0_NAME_TABLE;
	BG_Patterntable = PPU_Reg.R0 & BG_PATTERN_ADDR ? PPU_Mem.patterntable1 : PPU_Mem.patterntable0;//����pattern�׵�ַ
	y_scroll = y_axes + PPU_BG_VScrlOrg;  	//Scorll λ�ƺ���ʾ�е�Y����
	if(y_scroll > 239){
		y_scroll -= 240;
		nNameTable ^= NAME_TABLE_V_MASK; 		//��ֱ������Ļ���л�name table��
	}
    y_TitleLine = y_scroll >> 3; 				//title �к� 0~29��y�������8��
	dy_axes = y_scroll & 0x07;					//��8������
	dx_axes = PPU_BG_HScrlOrg & 0x07;			//x��ƫ������
	
	/*����ʾһ�е���߲���,�ӵ�һ�����ؿ�ʼɨ��*/
	Buffer_LineCnt = 8 - dx_axes;				//����д��λ��(0~ 255)��8����ʾ��ʼ��
	/*x_TitleLine ~ 31 ��������ʾ��8bitһ�У�*/
	for(x_TitleLine = PPU_BG_HScrlOrg >> 3; x_TitleLine < 32; x_TitleLine++){		   //��������һ����ʾtitle��Ԫ��ʼ
		BG_TitlePatNum = PPU_Mem.name_table[nNameTable][(y_TitleLine << 5) + x_TitleLine]; 	//y_TitleLine * 32,��ǰ��ʾ��title�ŵ� 
		L_byte = BG_Patterntable[(BG_TitlePatNum << 4) + dy_axes];							//BG_TitlePatNum * 16 + dy_xaes
		H_byte = BG_Patterntable[(BG_TitlePatNum << 4) + dy_axes + 8];
		//���Ա� �в��� ����λ��ɫ����ֵ						��4ȥ�����ٳ�8				��4			
		BG_attr_value = PPU_Mem.name_table[nNameTable][960 + ((y_TitleLine >> 2) << 3) + (x_TitleLine >> 2)];//title��Ӧ�����Ա�8bitֵ
		 //��title��Ӧ�ĸ���λ����y title bit2  ���� 1λ��(����)�� ��x title bit2������ֵ [000][010][100][110] 0 2 4 6Ϊ��Ӧ��attr 8bit[0:1][2:3][4:5][6:7] �еĸ���λ��ɫֵ
		BG_attr_value = ((BG_attr_value >> (((y_TitleLine & 2) << 1) | (x_TitleLine & 2))) & 3) << 2; 		
		/*x��ÿ��ɨ��8������ʾ*/
		for(i=7; i>=0; i--){							   //��д������ص���ɫ
			//[1:0]����λ��ɫ����ֵ
			BG_color_num = BG_attr_value;
			BG_color_num |=(L_byte >> i) & 1;				
			BG_color_num |=((H_byte >> i) & 1) << 1;
			if(BG_color_num & 3){			  //�������λΪ0����Ϊ͸��ɫ,��д��
				Buffer_scanline[Buffer_LineCnt] =  NES_Color_Palette[PPU_Mem.image_palette[BG_color_num]];
				Buffer_LineCnt++;
			}else{
				Buffer_LineCnt++;
			}
		}
	}
	/*��ʾһ���ұ߲���, �л�name table��*/
	nNameTable ^= NAME_TABLE_H_MASK;
	for (x_TitleLine = 0; x_TitleLine <= (PPU_BG_HScrlOrg >> 3); x_TitleLine++ ){
		BG_TitlePatNum = PPU_Mem.name_table[nNameTable][(y_TitleLine << 5) + x_TitleLine]; //y_TitleLine * 32,��ǰ��ʾ��title�ŵ� 
		L_byte = BG_Patterntable[(BG_TitlePatNum << 4) + dy_axes];				
		H_byte = BG_Patterntable[(BG_TitlePatNum << 4) + dy_axes + 8];
		BG_attr_value = PPU_Mem.name_table[nNameTable][960 + ((y_TitleLine >> 2) << 3) + (x_TitleLine >> 2)];//title��Ӧ�����Ա�8bitֵ
		BG_attr_value = ((BG_attr_value >> (((y_TitleLine & 2) << 1) | (x_TitleLine & 2))) & 3) << 2; 		  //������ɫ[4:3]
		for(i=7; i>=0; i--){
			BG_color_num = BG_attr_value;							   
			BG_color_num |=(L_byte >> i) & 1;				
			BG_color_num |=((H_byte >> i) & 1) << 1;
			if(BG_color_num & 3){			 
				Buffer_scanline[Buffer_LineCnt] = NES_Color_Palette[PPU_Mem.image_palette[BG_color_num]];
				Buffer_LineCnt++;
			}else{
				Buffer_LineCnt++;
			}
		}
	}
}

/*
 * ��ʾһ��sprite��title 88
 */
void NES_RenderSprPattern(SpriteType *sprptr, uint8 *Spr_Patterntable, uint16 title_addr, uint8 dy_axes)
{
	int	  i, dx_axes;
	uint8 Spr_color_num, H_byte, L_byte;
	
	if(((PPU_Reg.R1 & R1_SPR_LEFT8) == 0) && sprptr -> x < 8){		   //��ֹ��8��������ʾ
		dx_axes =  8 - sprptr -> x;
		if(dx_axes == 0)	return;		
	}else{
		dx_axes = 0;
	}
	if(sprptr -> attr & SPR_VFLIP){		//����ֱ��ת
	 	dy_axes = 7 - dy_axes; 			//sprite 8*8��ʾdy_axes��
	}
	L_byte = Spr_Patterntable[title_addr + dy_axes];
	H_byte = Spr_Patterntable[title_addr + dy_axes + 8];
	if(sprptr -> attr & SPR_HFLIP){	    							//��ˮƽ��ת
		for(i=7; i>=dx_axes; i--){									//��д�ұ� ��ɫ����
			Spr_color_num  = (L_byte >> i) & 1;						//bit0
			Spr_color_num |= ((H_byte >> i) & 1) << 1;				//bit1
			if(Spr_color_num == 0)	continue;
			Spr_color_num |= (sprptr -> attr & 0x03) << 2;			//bit23
			Buffer_scanline[sprptr -> x + i + 8] =  NES_Color_Palette[PPU_Mem.sprite_palette[Spr_color_num]]; //ƫ��8
		}
	}else{
		for(i=7; i>=dx_axes; i--){								//��д�ұ� ��ɫ����
			Spr_color_num  = (L_byte >> (7-i)) & 1;				//bit0
			Spr_color_num |= ((H_byte >> (7-i)) & 1) << 1;		//bit1
			if(Spr_color_num == 0)	continue;
			Spr_color_num |= (sprptr -> attr & 0x03) << 2;			//bit23
			Buffer_scanline[sprptr -> x + i + 8] =  NES_Color_Palette[PPU_Mem.sprite_palette[Spr_color_num]];//д����ɫֵ������

		} 
	}
}

/*
 * sprite 8*8 ��ʾ����ɨ��
 */
void NES_RenderSprite88(SpriteType *sprptr, int dy_axes)
{
	uint8  *Spr_Patterntable;	
	/*ȡ������title Pattern�׵�ַ*/
	Spr_Patterntable = (PPU_Reg.R0 & SPR_PATTERN_ADDR)	? PPU_Mem.patterntable1 : PPU_Mem.patterntable0;
	NES_RenderSprPattern(sprptr, Spr_Patterntable, sprptr -> t_num << 4, (uint8)dy_axes);
}

/*
 * sprite 8*16 ��ʾ����ɨ��
 */			
void NES_RenderSprite16(SpriteType *sprptr, int dy_axes)
{
	if(sprptr -> t_num & 0x01){										
		if(dy_axes < 8)	 //sprite  title ������
			NES_RenderSprPattern(sprptr, PPU_Mem.patterntable1, (sprptr -> t_num & 0xFE) << 4, (uint8)dy_axes);	   //��8*8
		else
			NES_RenderSprPattern(sprptr, PPU_Mem.patterntable1, sprptr -> t_num << 4, (uint8)dy_axes & 7);		   //��8*8
	}else{
		if(dy_axes < 8)	//sprite  title ż����
			NES_RenderSprPattern(sprptr, PPU_Mem.patterntable0, sprptr -> t_num << 4, (uint8)dy_axes);			   //��8*8
		else
			NES_RenderSprPattern(sprptr, PPU_Mem.patterntable0, (sprptr -> t_num | 1) << 4, (uint8)dy_axes & 7);   //��8*8
	}
}
/*
 * ���
 */
void clear(void)
{
   mrc_memset(Buffer_scanline,0,sizeof(Buffer_scanline));
}
/*
 * PPU ��ʾһ��
 */
void NES_RenderLine(int y_axes)
{
	int16 i, render_spr_num, spr_size, dy_axes;


	PPU_Reg.R2 &= ~R2_LOST_SPR;											//����PPU״̬�Ĵ���R2 SPR LOST�ı�־λ


	if(PPU_Reg.R1 & (R1_BG_VISIBLE | R1_SPR_VISIBLE)){					//��Ϊ�٣��ر���ʾ����0��
		/*�����ʾ���棬�ڴ����õױ���ɫ����ȷ����*/
		for(i=7; i<256 ; i++)
		{						//��ʾ�� 7 ~ 263  0~7 263~270 Ϊ��ֹ�����
		   Buffer_scanline[i] =  NES_Color_Palette[PPU_Mem.image_palette[0]];
		}	
		//clear();
		spr_size = PPU_Reg.R0 & R0_SPR_SIZE	? 0x0F : 0x07;				//spr_size 8��0~7��16: 0~15
		/* ɨ�豳��sprite��ת������ʾ����д�뵽����,ÿһ�����ֻ����ʾ8��Sprite*/
		if(PPU_Reg.R1 & R1_SPR_VISIBLE){								//������sprite��ʾ
			render_spr_num=0;											//������ʾ������
		 	for(i=63; i>=0; i--){										//���ص�sprites 0 ������ʾ������ȼ����������ȼ�˳���֮������������ʾ������ȼ�
				/*�ж���ʾ�㣨�ǣ� ����*/
				if(!(sprite[i].attr & SPR_BG_PRIO))	continue;			 //(0=Sprite In front of BG, 1=Sprite Behind BG)
				/*�ж���ʾλ��*/
				dy_axes = y_axes - (uint8)(sprite[i].y + 1);			//�ж�sprite�Ƿ��ڵ�ǰ����ʾ��Χ��,sprite y (FF,00,01,...EE)(0~239)
				if(dy_axes != (dy_axes & spr_size))	continue;			//�������򷵻ؼ���ѭ��������һ��
				/*������sprite�ڵ�ǰ��ʾ��,��ת��������ʾ�׶�*/
				render_spr_num++;										//����ʾ��sprite����Ŀ+1
				if(render_spr_num > 8 ){								//һ�г���8��spreite������ѭ��
					PPU_Reg.R2 |= R2_LOST_SPR;						   	//����PPU״̬�Ĵ���R2�ı�־λ
					break;
				}
				if(PPU_Reg.R0 & R0_SPR_SIZE){							//��Ϊ�棬sprite�Ĵ�С8*16
					NES_RenderSprite16(&sprite[i], dy_axes);
				}else{													//��Ϊ�٣�sprite�Ĵ�С8*8
					NES_RenderSprite88(&sprite[i], dy_axes);
				}
			}	
		}
	
		/* ɨ�豳�� background*/
		if(PPU_Reg.R1 & R1_BG_VISIBLE)
		{
			NES_RenderBGLine(y_axes);									//ɨ�貢����Sprite #0��ײ��־
		}
	
		/* ɨ��ǰ��sprite��ת������ʾ����д�뵽����,ÿһ�����ֻ����ʾ8��Sprite*/
		if(PPU_Reg.R1 & R1_SPR_VISIBLE){								//������sprite��ʾ
			render_spr_num=0;											//������ʾ������
		/* ���ص�sprites 0 ������ʾ������ȼ����������ȼ�˳���֮������������ʾ������ȼ�
		 * ��ע����ǰ��sprites ���ȼ����ڱ������ȼ����ص�����ɫ��ǰ�����ȼ����ڱ������ȼ��Ļ���ǰ����������ʾ(��δ����)*/
		 	for(i=63; i>=0; i--){										
				/*�ж���ʾ�� ǰ��*/
				if(sprite[i].attr & SPR_BG_PRIO)	continue;			 //(0=Sprite In front of BG, 1=Sprite Behind BG)
				/*�ж���ʾλ��*/
				dy_axes = y_axes - ((int)sprite[i].y + 1);				//�ж�sprite�Ƿ��ڵ�ǰ����ʾ��Χ��,sprite y (FF,00,01,...EE)(0~239)
				if(dy_axes != (dy_axes & spr_size))	continue;			//�������򷵻ؼ���ѭ��������һ��
				/*������sprite�ڵ�ǰ��ʾ��,��ת��������ʾ�׶�*/
				render_spr_num++;										//����ʾ��sprite����Ŀ+1
				if(render_spr_num > 8 ){								//һ�г���8��spreite������ѭ��
					PPU_Reg.R2 |= R2_LOST_SPR;						   	//����PPU״̬�Ĵ���R2�ı�־λ
					break;
				}
				if(PPU_Reg.R0 & R0_SPR_SIZE){							//��Ϊ�棬sprite�Ĵ�С8*16
					NES_RenderSprite16(&sprite[i], dy_axes);
				}else{													//��Ϊ�٣�sprite�Ĵ�С8*8
					NES_RenderSprite88(&sprite[i], dy_axes);
				}
			}	
		}
	}
	else
	{
	  clear();
	}
	/*���ɨ�裬������ʾ����д��LCD*/
	//NES_LCD_DisplayLine(y_axes, Buffer_scanline);	
		mrc_memcpy((char*)(LCDBUF+(y_axes*256)),(char*)(Buffer_scanline+8),248*2);
}

/*
 * PPU ���л��棬д��LCD
 */


/*void NES_LCD_DisplayLine(int y_axes, uint16 *Disaplyline_buffer)
//{
	uint16 index;
	uint16 j=0;//264
	for(index = 8; index < 248; index++)
	{
	j=j%257;
	LCDBUF[j+(240*y_axes)]=(uint16)Buffer_scanline[index];
	j++;
	}
}*/


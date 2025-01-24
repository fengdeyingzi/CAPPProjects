java -jar D:\app\mrpbuilder.jar -t clear
java -jar D:\app\mrpbuilder.jar -t gcc -o libcapp.dll -Isrc -i main.c map.c array.c enemy.c enemys.c hero.c readtext.c tield.c tmx_world.c tmx.c world_hero.c src\ -liconv
@REM gcc -shared -o libcapp.dll -Isrc -I.\ src\base.c src\graphics.c src\exb.c src\ex_math.c src\xl_coding.c main.c map.c enemy.c -liconv
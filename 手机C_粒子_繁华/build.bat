java -jar D:\app\mrpbuilder.jar -t clear
java -jar D:\app\mrpbuilder.jar -t gcc -o libcapp.dll -Isrc -I..\src -i main.c src\ ..\src -liconv
@REM gcc -shared -o libcapp.dll -Isrc -I.\ src\base.c src\graphics.c src\exb.c src\ex_math.c src\xl_coding.c main.c map.c enemy.c -liconv
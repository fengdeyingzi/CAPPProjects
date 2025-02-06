java -jar D:\app\mrpbuilder.jar -t clear
java -jar D:\app\mrpbuilder.jar -t gcc -o libcapp.dll -Isrc -Isrc\api -i main.c hero.c enemy.c src\ src\api src\game src\tools src\xgui -liconv

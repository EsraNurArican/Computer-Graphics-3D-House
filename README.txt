CSE 461 COMPUTER GRAPHICS HW1
Ödevde opengl ve glut kütüphanesi kullanılmıştır.
Programı windows ortamında çalıştırmak için VisualStudio üzerinde kodu açtıktan sonra ManageNugetPackages kısmından gerekli kütüphanleri indirmelisiniz.
Sonrasında Local Windows Debugger butonuna basarak kodu çalıştırabilirsiniz
Programı ubuntu ortamında çalıştırmak isterseniz:
	-OpenGL/Glut library'si kurulu değilse indirmek için:
		 $ sudo apt-get install libglut3-dev komutunu yazın.
		 $ sudo apt-cache search glut
		 $ dpkg -L freeglut3-dev komutu ile indirilen paketlerin tümünü görebilirsiniz
	-Ubuntu ortamında OpenGL/Glut kurulu ise terminalde kodu çalıştırmak için:
		 $ g++ -o out hw1.cpp -lGL -lGLU -lglut
		 $ ./out
		komutlarını yazarak programı çalıştırabilirsiniz.
	Programdan çıkmak için esc tuşunu kullanabilirsiniz.

Video link: https://youtu.be/vTd6mhtYQcE
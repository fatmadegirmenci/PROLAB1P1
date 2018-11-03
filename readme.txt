Trafik Ak���n�n Modellenmesi

Fatma De�irmenci  -	170201008
Berfin K�semen	  -	170201058

Bu readme.txt dosyas�, Trafik Ak���n�n Modellenmesi projesine aittir.
Bu paket, kaynak kodu ile ayn� dizin i�erisinde bulunacakt�r.


1-PAKET�N ��ER���:
-------------------
170201008-170201058.txt - Projenin tek dosyaya indirgenmi� salt kaynak kodu.
readme.txt - Bu dosya.
kaynak.zip - Projenin kaynak kodunun ve yard�mc� dosyalar�n ziplenmi� hali.
rapor.doc - Proje raporu.
-------------------


2-S�STEM GEREKS�N�MLER�:
-------------------
gcc - GNU Compiler Colection - http://gcc.gnu.org/
-------------------


3-KURULUM:
-------------------
Paket i�eri�ini yukar�da g�rebilirsiniz.

Bu kod, iki adet Windows kurulu makinede �al��t�r�ld�:
- Fatma'n�n Windows 10 y�kl� diz�st� bilgisayar�nda.
- Berfin'in Windows 10 y�kl� masa�st� bilgisayar�nda.

Bu iki durumda da kod, herhangi bir hata vermeden, daha �nceden belirlenen kriterlere
uygun �al��t�.

Windows harici bir makinede �al��t�rmak istiyorsan�z, kaynak kodu Windows
ba��ml�l�klar�ndan ay�r�p derlemeniz gerekiyor.

-------------------


4-KODU DERLEMEK:
------------------
Art�k bilgisayar�m�zda kurulu olan GCC ile kodu kolayca derleyebiliriz.

Windows i�in:

>gcc 170201008-170201058.cpp �o 170201008-170201058.exe

Linux / Unix i�in:

>gcc 170201008-170201008.cpp -o 170201008-170201058


Derleme bittikten sonra kolayca program� �al��t�rabilirsiniz.
------------------


5- PARAMETRELER
---------------------------
Kodun �al��mas� i�in ba�lang��ta herhangi bir parametre gerekmiyor.
------------------


6- PROGRAMIN KULLANIMI
-----------------------------
Trafik Ak���n�n Modellenmesi, kullan�c�dan, her yol i�in y�n bilgisi
ve ortalama ara� say�s� alarak, bilinmeyen yollar�n ortalama ara�
say�s�n�n Gauss-Jordan ile bulunup, ekrana yazd�r�lmas�n� sa�lar.

Ekrana 2 harita da yazd�r�l�r ve kullan�c�dan se�im yapmas� istenilir.
Yaln�zca 1 ya da 2 se�imini yapabilir.

Harita se�iminin ard�ndan, se�ilen giri� ve ��k�� yollar�nda, en 
fazla 2 giri� ve 2 ��k�� se�ilebilir.

Se�ilen haritaya g�re kullan�c�dan her yolun y�n ve ba�lang�� noktas�
bilgisi al�n�r. D���mlerde �ak��ma olmas� halinde bir yolun y�n�n�n
de�i�tirilmesi istenilir. 

Se�ilen y�nler hareketli bir �ekilde ekranda g�sterilir. Bu ekrandan
��kmak i�in bir tu�a bas�lmal�d�r.

Her yol i�in, kullan�c�dan ortalama ara� say�s� bilgisi al�n�r. Bilinmeyen
yollar i�in -1 de�eri girilmelidir. T�m yollar�n ortalama ara� say�s� 
giri�i bitti�inde e�er 1'den az ya da 5'ten �ok bilinmeyen yol giri�i
yap�lm�� ise, program bilinmeyen yollar�n ara� yo�unlu�unu hesaplayamaz.

Verilen y�n bilgisi ve ortalama ara� say�lar� kapsam�nda, denklemlere g�re
katsay�lar� bir matrise atama i�lemi ger�ekle�tikten sonra denklem sistemi
��z�l�rken yap�lan her ad�m ekranda kullan�c�ya g�sterilecektir.

Denklem sistemi ��z�ld�kten sonra ��z�m�n�n olup olmad��� ekrana yazd�r�lacak
ve programdan ��k�lacakt�r.

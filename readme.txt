Trafik Akýþýnýn Modellenmesi

Fatma Deðirmenci  -	170201008
Berfin Kösemen	  -	170201058

Bu readme.txt dosyasý, Trafik Akýþýnýn Modellenmesi projesine aittir.
Bu paket, kaynak kodu ile ayný dizin içerisinde bulunacaktýr.


1-PAKETÝN ÝÇERÝÐÝ:
-------------------
170201008-170201058.txt - Projenin tek dosyaya indirgenmiþ salt kaynak kodu.
readme.txt - Bu dosya.
kaynak.zip - Projenin kaynak kodunun ve yardýmcý dosyalarýn ziplenmiþ hali.
rapor.doc - Proje raporu.
-------------------


2-SÝSTEM GEREKSÝNÝMLERÝ:
-------------------
gcc - GNU Compiler Colection - http://gcc.gnu.org/
-------------------


3-KURULUM:
-------------------
Paket içeriðini yukarýda görebilirsiniz.

Bu kod, iki adet Windows kurulu makinede çalýþtýrýldý:
- Fatma'nýn Windows 10 yüklü dizüstü bilgisayarýnda.
- Berfin'in Windows 10 yüklü masaüstü bilgisayarýnda.

Bu iki durumda da kod, herhangi bir hata vermeden, daha önceden belirlenen kriterlere
uygun çalýþtý.

Windows harici bir makinede çalýþtýrmak istiyorsanýz, kaynak kodu Windows
baðýmlýlýklarýndan ayýrýp derlemeniz gerekiyor.

-------------------


4-KODU DERLEMEK:
------------------
Artýk bilgisayarýmýzda kurulu olan GCC ile kodu kolayca derleyebiliriz.

Windows için:

>gcc 170201008-170201058.cpp –o 170201008-170201058.exe

Linux / Unix için:

>gcc 170201008-170201008.cpp -o 170201008-170201058


Derleme bittikten sonra kolayca programý çalýþtýrabilirsiniz.
------------------


5- PARAMETRELER
---------------------------
Kodun çalýþmasý için baþlangýçta herhangi bir parametre gerekmiyor.
------------------


6- PROGRAMIN KULLANIMI
-----------------------------
Trafik Akýþýnýn Modellenmesi, kullanýcýdan, her yol için yön bilgisi
ve ortalama araç sayýsý alarak, bilinmeyen yollarýn ortalama araç
sayýsýnýn Gauss-Jordan ile bulunup, ekrana yazdýrýlmasýný saðlar.

Ekrana 2 harita da yazdýrýlýr ve kullanýcýdan seçim yapmasý istenilir.
Yalnýzca 1 ya da 2 seçimini yapabilir.

Harita seçiminin ardýndan, seçilen giriþ ve çýkýþ yollarýnda, en 
fazla 2 giriþ ve 2 çýkýþ seçilebilir.

Seçilen haritaya göre kullanýcýdan her yolun yön ve baþlangýç noktasý
bilgisi alýnýr. Düðümlerde çakýþma olmasý halinde bir yolun yönünün
deðiþtirilmesi istenilir. 

Seçilen yönler hareketli bir þekilde ekranda gösterilir. Bu ekrandan
çýkmak için bir tuþa basýlmalýdýr.

Her yol için, kullanýcýdan ortalama araç sayýsý bilgisi alýnýr. Bilinmeyen
yollar için -1 deðeri girilmelidir. Tüm yollarýn ortalama araç sayýsý 
giriþi bittiðinde eðer 1'den az ya da 5'ten çok bilinmeyen yol giriþi
yapýlmýþ ise, program bilinmeyen yollarýn araç yoðunluðunu hesaplayamaz.

Verilen yön bilgisi ve ortalama araç sayýlarý kapsamýnda, denklemlere göre
katsayýlarý bir matrise atama iþlemi gerçekleþtikten sonra denklem sistemi
çözülürken yapýlan her adým ekranda kullanýcýya gösterilecektir.

Denklem sistemi çözüldükten sonra çözümünün olup olmadýðý ekrana yazdýrýlacak
ve programdan çýkýlacaktýr.

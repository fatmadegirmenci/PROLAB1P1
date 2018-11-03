#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <ctype.h>

/**
 * Ad: Trafik Akisinin Modellenmesi
 * Aciklama: Secilen haritaya gore bilinmeyen yollarin ortalama 
 *			 arac sayisini Gauss-Jordan Eleme Metodu ile bulur.
 * Tarih: 29 Ekim 2018
 * Yapimci: Fatma Degirmenci & Berfin Kosemen
 * Numaralar: 170201008 & 170201058
 *
 * =============================================================================
 *
 * LISANS: MIT Ozgur Lisansi, Kaynak: http://ozgurlisanslar.org.tr/mit/
 *
 * Telif Hakki (c) 1998, 1999, 2000 Thai Acik Kaynak Yazilim Merkezi Ltd.
 *
 * Hicbir ucret talep edilmeden burada isbu yazilimin bir kopyasini ve
 * belgelendirme dosyalarini (“Yazilim”) elde eden herkese verilen izin;
 * kullanma, kopyalama, degistirme, birlestirme, yayimlama, dagitma, alt
 * lisanslama, ve/veya yazilimin kopyalarini satma eylemleri de dahil
 * olmak uzere ve bununla kisitlama olmaksizin, yazilimin sinirlama
 * olmadan ticaretini yapmak icin verilmis olup, bunlari yapmalari icin
 * yazilimin saglandigi kisilere asagidakileri yapmak kosuluyla sunulur:
 *
 * Yukaridaki telif hakki bildirimi ve isbu izin bildirimi yazilimin tum
 * kopyalarina veya onemli parcalarina eklenmelidir.
 *
 * YAZILIM “HICBIR DEGISIKLIK YAPILMADAN” ESASINA BAGLI OLARAK, TICARETE
 * ELVERISLILIK, OZEL BIR AMACA UYGUNLUK VE IHLAL OLMAMASI DA DAHIL VE
 * BUNUNLA KISITLI OLMAKSIZIN ACIKCA VEYA USTU KAPALI OLARAK HICBIR TEMINAT
 * OLMAKSIZIN SUNULMUSTUR. HICBIR KOSULDA YAZARLAR VEYA TELIF HAKKI SAHIPLERI
 * HERHANGI BIR IDDIAYA, HASARA VEYA DIGER YUKUMLULUKLERE KARSI, YAZILIMLA
 * VEYA KULLANIMLA VEYA YAZILIMIN BASKA BAGLANTILARIYLA ILGILI, BUNLARDAN
 * KAYNAKLANAN VE BUNLARIN SONUCU BIR SOZLESME DAVASI, HAKSIZ FIIL VEYA
 * DIGER EYLEMLERDEN SORUMLU DEGILDIR.
 */


//FONKSIYONLAR
void yolYazdir();
int kullaniciHaritaGirisi();
void girisSecimi(int);
void yonsecimi(int);
void hareketliYonlerIcinMap(int);
void yonleriHareketliYazdir(int);
void OrtAracSayisi(int) ;
void denklemCikarma(int);
void lineerEselon(float Array[][6],int n);

//YAPILAR
struct yonbul{
   char baslangicnoktasi;
   char yon;
};

struct yol{
  char isim;
  int ortarac; //ortalama arac sayisi
  struct yonbul git; //yolun gidis yonu ve baslangic noktasi icin kullanilmistir
}yollar[9];


int main()
{
	yolYazdir();
	
    int haritasecim = kullaniciHaritaGirisi();
    while (getchar() != '\n');
    
    girisSecimi(haritasecim);
    yonsecimi(haritasecim);
	yonleriHareketliYazdir(haritasecim);
    OrtAracSayisi(haritasecim);
    denklemCikarma(haritasecim);
    
    return 0;
}

void yolYazdir(){
	/* Olculer*/
	/* Sagdan sola dogru ilk bosluk 25, yol uzunlugu 40, yaricap 75, yol arasi 40, yaricap 75, yol uzunlugu 40, bosluk 25*/
	/* Yukaridan asagi dogru ilk bosluk 15, yol uzunlugu 40, yaricap 75, yol arasi 40, yaricap 75, yol uzunlugu 40 */
	
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	
	//************************ARKAPLAN BEYAZ YAPMA************************
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 0, 800, 500);

	//************************YOL 1 SIYAH YUVARLAK KISIM (a,b,c,d)************************	
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	pieslice(160,150,0,360,95);
	
	//************************YOL 1 EN IC KISMINDAKI BEYAZ YUVARLAK KISIM************************
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	pieslice(160,150,0,360,48);

	//************************YOL 1 KAHVERENGI CIZGILER 1************************
	setlinestyle(0,0,2);
	setcolor(BROWN);
	circle(160, 150, 90); //dýs yuvarlak
	circle(160, 150, 53); //orta yuvarlak
	
	//************************YOL 1 YANDAKI DIKDORTGEN YOLLAR (x,y,z,t)************************
	setfillstyle(SOLID_FILL, BLACK);
	bar(140,15,180,63); //ust yol //bar(140,15,180,58); //ust yol
	
	setfillstyle(SOLID_FILL, BLACK);
	bar(140,237,180,285); //alt yol //bar(140,242,180,285); //alt yol
	
	setfillstyle(SOLID_FILL, BLACK);
	bar(25,129,73,169); //sol yol //bar(25,129,68,169); //sol yol
	
	setfillstyle(SOLID_FILL, BLACK);
	bar(247,129,295,169); //sag yol //bar(252,129,295,169); //sag yol
	
	//************************YOL 1 UZERINDEKI KESIKLI BEYAZ CIZGILER************************
	setcolor(WHITE);
	setlinestyle(1,0,1);
	circle(160,150,70);
	
	line(26,149,90,149); //sol yol cizgisi  
	line(230, 149, 294, 149); //sag yol cizgisi
	line(160,16,160, 80); //ust yol cizgisi
	line(160, 220, 160, 284); //alt yol cizgisi
	
	//************************YOL 1 KAHVERENGI CIZGILER 2************************
	setlinestyle(0,0,2);
	setcolor(BROWN);
	line(144,15,144,60); //ust yol sol cizgi
	line(176,15,176,60); //ust yol sag cizgi
	line(25, 133, 70, 133); //sol yol ust cizgi
	line(25, 165, 70, 165);  //sol yol alt cizgi
	line(250, 133, 294, 133); //sag yol ust cizgi
	line(250, 165, 294, 165); //sag yol alt cizgi
	line(144,239,144,284); //alt yol sol cizgi
	line(176,239, 176, 284); //alt yol sag cizgi
	//************************HARITA 1 YAZDIRMA SONU************************

	setcolor(BLACK);
	setlinestyle(0,0,1);
	
	//************************YOL 2 SIYAH YUVARLAK KISMI (a,b,c,d)************************	
	setcolor(BLACK);
	setfillstyle(SOLID_FILL, BLACK);
	pieslice(455,150,0,360,95);
	
	//************************YOL 2 EN IC KISMINDAKI BEYAZ YUVARLAK KISIM************************
	setcolor(WHITE);
	setfillstyle(SOLID_FILL, WHITE);
	pieslice(455,150,0,360,48);
	
	//************************YOL 2 KAHVERENGI CIZGILER 1************************
	setlinestyle(0,0,2);
	setcolor(BROWN);
	circle(455,150, 53); //orta yuvarlak
	circle(455, 150, 90); //dýs yuvarlak
	
	//************************YOL 2 YANDAKI DIKDORTGEN YOLLAR (x,y,z,t)************************
	setfillstyle(SOLID_FILL, BLACK);
	bar(435,15,475,63); //ust yol
	
	setfillstyle(SOLID_FILL, BLACK);
	bar(435,237,475,285); //alt yol
	
	setfillstyle(SOLID_FILL, BLACK);
	bar(320,129,368,169); //sol yol
	
	setfillstyle(SOLID_FILL, BLACK);
	bar(542,129,590,169); //sag yol
	
	setfillstyle(SOLID_FILL, BLACK);
	bar(365,129,535,169); //orta yol
	
	//************************YOL 1 UZERINDEKI KESIKLI BEYAZ CIZGILER************************
	setcolor(WHITE);
	setlinestyle(1,0,1);
	circle(455,150,70);
	
	line(321,149,385,149); //sol yol cizgisi  
	line(525, 149, 589, 149); //sag yol cizgisi
	line(455,16,455, 80); //ust yol cizgisi
	line(455, 220, 455, 284); //alt yol cizgisi
	line(408,149,502,149); //orta yol cizgisi
	
	//************************YOL 2 KAHVERENGI CIZGILER 2************************
	setlinestyle(0,0,2);
	setcolor(BROWN);
	line(320,133, 365, 133); //sol yol ust cizgi
	line(320,165, 365, 165); //sol yol alt cizgi
	line(545, 133, 589, 133); //sag yol ust cizgi
	line(545, 165, 589, 165); //sag yol alt cizgi
	line(439, 15, 439, 60); //ust yol sol cizgi
	line(471, 15, 471, 60); //ust yol sag cizgi
	line(439, 239, 439, 284); //alt yol sag cizgi
	line(471, 239, 471, 284); //alt yol sol cizgi
	line(405, 133, 505, 133); //orta yol ust cizgi
	line(405, 165, 505, 165); //orta yol alt cizgi
	//************************HARITA 2 YAZDIRMA SONU************************

	/************************YOLLAR UZERI TEXTLER**************************/
	setbkcolor(RED);
	setcolor(WHITE);
	settextstyle(6, HORIZ_DIR, 1);
	
	outtextxy(105, 90, "a");  
	outtextxy(200, 90, "b"); 
	outtextxy(200, 185, "d"); 
	outtextxy(105, 185, "c");
	outtextxy(155, 30, "x");
	outtextxy(155, 253, "z");
	outtextxy(45, 140, "t");
	outtextxy(265, 140, "y");
	
	outtextxy(400, 90, "a");  
	outtextxy(505, 90, "b");
	outtextxy(400, 185, "c"); 
	outtextxy(505, 185, "d"); 
	outtextxy(450, 30, "x");
	outtextxy(450, 253, "z");
	outtextxy(340, 140, "t");
	outtextxy(560, 140, "y");
	outtextxy(445, 140, "e");
	
	setbkcolor(0);
	settextstyle(8, HORIZ_DIR, 1);
	/************************YOL UZERI TEXTLER SONU*********************/
	
	setcolor(12);
	setbkcolor(WHITE);
	settextstyle(4, HORIZ_DIR, 3); // 4 is font, 3 is char size
	outtextxy(100, 320, "Harita 1");
	outtextxy(395, 320, "Harita 2");
	
	getch();
	closegraph();
}

void hareketliYonlerIcinMap(int haritaSecim) {
	
	if(haritaSecim == 1) {
		//ARKAPLAN BEYAZ
		setfillstyle(SOLID_FILL, WHITE);
		bar(0, 0, 800, 500);
		
		//YOLUN SIYAH YUVARLAK KISMI (a,b,c,d)
		setcolor(BLACK);
		setfillstyle(SOLID_FILL, BLACK);
		pieslice(160,150,0,360,95);
	
		//YOLUN EN IC KISMINDAKI BEYAZ YUVARLAK KISIM
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		pieslice(160,150,0,360,48);
	
		//KAHVERENGI CIZGILER 1
		setlinestyle(0,0,2);
		setcolor(BROWN);
		circle(160, 150, 90); //dýs yuvarlak
		circle(160, 150, 53); //orta yuvarlak
	
		//YANDAKI DIKDORTGEN YOLLAR (x,y,z,t)
		setfillstyle(SOLID_FILL, BLACK);
		bar(140,15,180,63); //ust yol 
		setfillstyle(SOLID_FILL, BLACK);
		bar(140,237,180,285); //alt yol 
		setfillstyle(SOLID_FILL, BLACK);
		bar(25,129,73,169); //sol yol 
		setfillstyle(SOLID_FILL, BLACK);
		bar(247,129,295,169); //sag yol 
	
		//YOL UZERINDEKI KESIKLI BEYAZ CIZGILER
		setbkcolor(BLACK);
		setcolor(WHITE);
		setlinestyle(1,0,1);
		circle(160,150,70);
		line(26,149,90,149); //sol yol cizgisi  
		line(230, 149, 294, 149); //sag yol cizgisi
		line(160,16,160, 80); //ust yol cizgisi
		line(160, 220, 160, 284); //alt yol cizgisi
	
		//KAHVERENGI CIZGILER 2
		setlinestyle(0,0,2);
		setcolor(BROWN);
		line(144,15,144,60); //ust yol sol cizgi
		line(176,15,176,60); //ust yol sag cizgi
		line(25, 133, 70, 133); //sol yol ust cizgi
		line(25, 165, 70, 165);  //sol yol alt cizgi
		line(250, 133, 294, 133); //sag yol ust cizgi
		line(250, 165, 294, 165); //sag yol alt cizgi
		line(144,239,144,284); //alt yol sol cizgi
		line(176,239, 176, 284); //alt yol sag cizgi
	
    	//YOL UZERI TEXTLER
		setbkcolor(RED);
		setcolor(WHITE);
		settextstyle(6, HORIZ_DIR, 1);
		outtextxy(105, 90, "a");  
		outtextxy(205, 90, "b"); 
		outtextxy(205, 185, "d"); 
		outtextxy(105, 185, "c");
		outtextxy(155, 30, "x");
		outtextxy(265, 140, "y");
		outtextxy(155, 253, "z");
		outtextxy(45, 140, "t");
    	setcolor(YELLOW);
    	setbkcolor(BLACK);
	}
    
	if(haritaSecim == 2) {
    	
		//ARKAPLAN BEYAZ YAPMA
    	setfillstyle(SOLID_FILL, WHITE);
		bar(0, 0, 800, 500);

		//YOLUN SIYAH YUVARLAK KISMI (a,b,c,d,e)
		setcolor(BLACK);
		setfillstyle(SOLID_FILL, BLACK);
		pieslice(160,150,0,360,95);
	
		//YOLUN EN IC KISMINDAKI BEYAZ YUVARLAK KISIM
		setcolor(WHITE);
		setfillstyle(SOLID_FILL, WHITE);
		pieslice(160,150,0,360,48);

		//KAHVERENGI CIZGILER 1
		setlinestyle(0,0,2);
		setcolor(BROWN);
		circle(160, 150, 90); //dýs yuvarlak
		circle(160, 150, 53); //orta yuvarlak
	
		//YANDAKI DIKDORTGEN YOLLAR (x,y,z,t)
		setfillstyle(SOLID_FILL, BLACK);
		bar(140,15,180,63); //ust yol 
		setfillstyle(SOLID_FILL, BLACK);
		bar(140,237,180,285); //alt yol 
		setfillstyle(SOLID_FILL, BLACK);
		bar(25,129,73,169); //sol yol 
		setfillstyle(SOLID_FILL, BLACK);
		bar(247,129,295,169); //sag yol
		setfillstyle(SOLID_FILL, BLACK);
		bar(105,129,215,169); //orta yol
	
		//YOL UZERINDEKI KESIKLI BEYAZ CIZGILER
		setbkcolor(BLACK);
		setcolor(WHITE);
		setlinestyle(1,0,1);
		circle(160,150,70);
		line(26,149,90,149); //sol yol cizgisi  
		line(230, 149, 294, 149); //sag yol cizgisi
		line(160,16,160, 80); //ust yol cizgisi
		line(160, 220, 160, 284); //alt yol cizgisi
		line(113,150,207,150); //orta yol cizgisi
	
		//KAHVERENGI CIZGILER 2
		setlinestyle(0,0,2);
		setcolor(BROWN);
		line(144,15,144,60); //ust yol sol cizgi
		line(176,15,176,60); //ust yol sag cizgi
		line(25, 133, 70, 133); //sol yol ust cizgi
		line(25, 165, 70, 165);  //sol yol alt cizgi
		line(250, 133, 294, 133); //sag yol ust cizgi
		line(250, 165, 294, 165); //sag yol alt cizgi
		line(144,239,144,284); //alt yol sol cizgi
		line(176,239, 176, 284); //alt yol sag cizgi
		line(110, 133, 210, 133); //orta yol ust cizgi
		line(110, 165, 210, 165); //orta yol alt cizgi
	
		//YOL UZERI TEXTLER
		setbkcolor(RED);
		setcolor(WHITE);
		settextstyle(6, HORIZ_DIR, 1);
		outtextxy(105, 90, "a");  
		outtextxy(205, 90, "b"); 
		outtextxy(205, 185, "d"); 
		outtextxy(105, 185, "c");
		outtextxy(155, 30, "x");
		outtextxy(155, 255, "z");
		outtextxy(45, 140, "t");
		outtextxy(265, 140, "y");
		outtextxy(155, 140, "e");
	
		setbkcolor(0);
		settextstyle(8, HORIZ_DIR, 1);
		
		setcolor(YELLOW);
	}	
}

void yonleriHareketliYazdir(int haritaSecim) {
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "C:\\TC\\BGI");
	
	//ARKAPLAN BEYAZ YAPMA
    setfillstyle(SOLID_FILL, WHITE);
	bar(0, 0, 800, 500);
		
	setcolor(12);
	setbkcolor(WHITE);
	settextstyle(3, HORIZ_DIR, 2); // 3 is font, 3 is char size
	outtextxy(100, 200, "Ilerlemek icin enter a basin.");
	outtextxy(100,230, "Tum yonler hareketli bir sekilde gösterilecektir.");
	outtextxy(100,260, "Yonler gosterilirken lutfen bekleyin.");
	
	getch();
	cleardevice();
	
	int salise = 1200;
	
	setlinestyle(0, 0, 3);
  	setcolor(YELLOW);
  		
	if(haritaSecim == 1) {
    	
  		hareketliYonlerIcinMap(haritaSecim);
  		delay(salise);
  		
    	//a yolunun okunu yazdirma
    	if(yollar[0].git.yon == 'x') {
    		arc(155, 140, 110, 160, 60); 
    		line(135, 84, 125, 80); // ust ok cizgisi 
    		line(135, 84, 125, 94); // alt ok cizgisi 
		}
		else{
			arc(155, 140, 110, 160, 60);               
			line(99, 120, 109, 110); // sag ok cizgisi  
    		line(99, 120, 95, 110); // sol ok cizgisi  
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
		
		//b yolunun okunu yazdirma
    	if(yollar[1].git.yon == 'x') {
    		arc(165, 140, 20, 70, 60); 
    		line(183, 83, 193, 78); // ust ok cizgisi 
    		line(183, 83, 193, 93); // alt ok cizgisi   
		}
		else{
    		arc(165, 140, 20, 70, 60);  
			line(222, 120, 227, 110); // sag ok cizgisi   
    		line(222, 120, 207, 110); // sol ok cizgisi   
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
		
		//c yolunun okunu yazdirma
    	if(yollar[2].git.yon == 't') {
    		arc(155, 160, 200, 250, 60);  					
    		line(100, 180, 110, 190); // sag ok cizgisi  
    		line(100, 180, 95, 190); // sol ok cizgisi 
		}
		else{
			arc(155,160,200,250,60); 
			line(135,215,125,205);  //ust ok cizgisi 
    		line(135,215,125,220);  // alt ok cizgisi 	
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
		
		//d yolunun okunu yazdirma
    	if(yollar[3].git.yon == 'y') {
   			arc(165, 160, 290, 340, 60);				
    		line(220, 178, 210, 188); // sol ok cizgisi 
    		line(220, 178, 225, 188); // sag ok cizgisi  
		}
		else{
    		arc(165,160,290,340,60); 
			line(185,215,195,205); // ust ok cizgisi   	
    		line(185,215,195,220);  // alt ok cizgisi  	
		}
		
		delay(salise);	
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
		
		//x yolunun okunu yazdirma
    	if(yollar[4].isim == 'x' || yollar[5].isim == 'x') {
 			line(160, 20, 160, 50); 
 			line(160, 50, 150, 40); //sol ok cizgisi  
 			line(160, 50, 170, 40); //sag ok cizgisi 
		}
		else{
			line(160, 20, 160, 50); 
			line(160, 20, 150, 30); //sol ok cizgisi 
			line(160, 20, 170, 30); //sag ok cizgisi
		}
		
		delay(salise);		
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
		
		//y yolunun okunu yazdirma
    	if(yollar[4].isim == 'y' || yollar[5].isim == 'y') {
    		line(290, 150, 260, 150);
    		line(260, 150, 270, 140); //ust ok cizgisi
    		line(260, 150, 270, 160); //alt ok cizgisi
		}
		else{
			line(290, 150, 260, 150);
			line(290, 150, 280, 140); //ust ok cizgisi
			line(290, 150, 280, 160); //alt ok cizgisi
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);	
			
		//z yolunun okunu yazdirma
    	if(yollar[4].isim == 'z' || yollar[5].isim == 'z') {
    		line(160, 250, 160, 280);
			line(160, 250, 150, 260); //sol ok cizgisi
			line(160, 250, 170, 260); //sag ok cizgisi
		}
		else{
			line(160, 250, 160, 280);
			line(160, 280, 150, 270); //sol ok cizgisi
			line(160, 280, 170, 270); //sag ok cizgisi
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
		
		//t yolunun okunu yazdirma
    	if(yollar[4].isim == 't' || yollar[5].isim == 't') {
    		line(30, 150, 60, 150);
    		line(60, 150, 50, 140); //ust ok cizgisi
   			line(60, 150, 50, 160); //alt ok cizgisi
		}
		else{
			line(30, 150, 60, 150);
			line(30, 150, 40, 140); //ust ok cizgisi
			line(30, 150, 40, 160); //alt ok cizgisi
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
		
		//**********************TUM YONLERI AYNI ANDA YAZDIRMA BASLANGIC*****************
		//a yolunun okunu yazdirma
    	if(yollar[0].git.yon == 'x') {
    		arc(155, 140, 110, 160, 60); 
    		line(135, 84, 125, 80); // ust ok cizgisi 
    		line(135, 84, 125, 94); // alt ok cizgisi 
		}
		else{
			arc(155, 140, 110, 160, 60);               
			line(99, 120, 109, 110); // sag ok cizgisi  
    		line(99, 120, 95, 110); // sol ok cizgisi  
		}
		//b yolunun okunu yazdirma
    	if(yollar[1].git.yon == 'x') {
    		arc(165, 140, 20, 70, 60); 
    		line(183, 83, 193, 78); // ust ok cizgisi 
    		line(183, 83, 193, 93); // alt ok cizgisi   
		}
		else{
    		arc(165, 140, 20, 70, 60);  
			line(222, 120, 227, 110); // sag ok cizgisi   
    		line(222, 120, 207, 110); // sol ok cizgisi   
		}
		//c yolunun okunu yazdirma
    	if(yollar[2].git.yon == 't') {
    		arc(155, 160, 200, 250, 60);  					
    		line(100, 180, 110, 190); // sag ok cizgisi  
    		line(100, 180, 95, 190); // sol ok cizgisi 
		}
		else{
			arc(155,160,200,250,60); 
			line(135,215,125,205);  //ust ok cizgisi 
    		line(135,215,125,220);  // alt ok cizgisi 	
		}
		//d yolunun okunu yazdirma
    	if(yollar[3].git.yon == 'y') {
   			arc(165, 160, 290, 340, 60);				
    		line(220, 178, 210, 188); // sol ok cizgisi 
    		line(220, 178, 225, 188); // sag ok cizgisi  
		}
		else{
    		arc(165,160,290,340,60); 
			line(185,215,195,205); // ust ok cizgisi   	
    		line(185,215,195,220);  // alt ok cizgisi  	
		}
		//x yolunun okunu yazdirma	
    	if(yollar[4].isim == 'x' || yollar[5].isim == 'x') {
 			line(160, 20, 160, 50); 
 			line(160, 50, 150, 40); //sol ok cizgisi  
 			line(160, 50, 170, 40); //sag ok cizgisi 
		}
		else{
			line(160, 20, 160, 50); 
			line(160, 20, 150, 30); //sol ok cizgisi 
			line(160, 20, 170, 30); //sag ok cizgisi
		}
		//y yolunun okunu yazdirma
    	if(yollar[4].isim == 'y' || yollar[5].isim == 'y') {
    		line(290, 150, 260, 150); 
    		line(260, 150, 270, 140); //ust ok cizgisi
    		line(260, 150, 270, 160); //alt ok cizgisi
		}
		else{
			line(290, 150, 260, 150);
			line(290, 150, 280, 140); //ust ok cizgisi
			line(290, 150, 280, 160); //alt ok cizgisi
		}
		//z yolunun okunu yazdirma
    	if(yollar[4].isim == 'z' || yollar[5].isim == 'z') {
    		line(160, 250, 160, 280);
			line(160, 250, 150, 260); //sol ok cizgisi
			line(160, 250, 170, 260); //sag ok cizgisi
		}
		else{
			line(160, 250, 160, 280);
			line(160, 280, 150, 270); //sol ok cizgisi
			line(160, 280, 170, 270); //sag ok cizgisi
		}
		//t yolunun okunu yazdirma
    	if(yollar[4].isim == 't' || yollar[5].isim == 't') {
    		line(30, 150, 60, 150);
    		line(60, 150, 50, 140); //ust ok cizgisi
   			line(60, 150, 50, 160); //alt ok cizgisi
		}
		else{
			line(30, 150, 60, 150);
			line(30, 150, 40, 140); //ust ok cizgisi
			line(30, 150, 40, 160); //alt ok cizgisi
		}
		//*********************TUM YONLERI AYNI ANDA YAZDIRMA SON********************
		
		setcolor(12);
		setbkcolor(WHITE);
		settextstyle(3, HORIZ_DIR, 2);
		outtextxy(50,350,"Tum yonler gosterildi. Cikmak icin enter a basin.");
		
		getch();
		closegraph();
	}
	
	if(haritaSecim == 2) {
  		
  		hareketliYonlerIcinMap(haritaSecim);
  		delay(salise);
		
    	//a yolunun okunu yazdirma
    	if(yollar[0].git.yon == 'x') {
    		arc(155, 140, 110, 160, 60); 
    		line(135, 84, 125, 80); // ust ok cizgisi 
    		line(135, 84, 125, 94); // alt ok cizgisi 
		}
		else{
			arc(155, 140, 110, 160, 60);               
			line(99, 120, 109, 110); // sag ok cizgisi  
    		line(99, 120, 95, 110); // sol ok cizgisi  
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
  		
		//b yolunun okunu yazdirma
    	if(yollar[1].git.yon == 'x') {
    		arc(165, 140, 20, 70, 60); 
    		line(183, 83, 193, 78); // ust ok cizgisi 
    		line(183, 83, 193, 93); // alt ok cizgisi   
		}
		else{
    		arc(165, 140, 20, 70, 60); 
			line(222, 120, 227, 110); // sag ok cizgisi   
    		line(222, 120, 207, 110); // sol ok cizgisi   
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
		
		//c yolunun okunu yazdirma
    	if(yollar[2].git.yon == 't') {
    		arc(155, 160, 200, 250, 60);  				
    		line(100, 180, 110, 190); // sag ok cizgisi 
    		line(100, 180, 95, 190); // sol ok cizgisi 
		}
		else{
			arc(155,160,200,250,60); 
			line(135,215,125,205);  //ust ok cizgisi 
    		line(135,215,125,220);  // alt ok cizgisi 	
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
  	
		//d yolunun okunu yazdirma
    	if(yollar[3].git.yon == 'y') {
   			arc(165, 160, 290, 340, 60);				
    		line(220, 178, 210, 188); // sol ok cizgisi 
    		line(220, 178, 225, 188); // sag ok cizgisi  
		}
		else{
    		arc(165,160,290,340,60);
			line(185,215,195,205); // ust ok cizgisi   	
    		line(185,215,195,220);  // alt ok cizgisi  
		}
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
  	
		//e yolunun okunu yazdirma
    	if(yollar[4].git.yon == 't') {
   			line(135, 150, 180, 150);
   			line(135, 150, 145, 140); //ust ok cizgisi
   			line(135, 150, 145, 160); //alt ok cizgisi
		}
		else{
    		line(135, 150, 180, 150);
    		line(180, 150, 170, 140); //ust ok cizgisi
   			line(180, 150, 170, 160); //alt ok cizgisi 
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);

    	if(yollar[5].isim == 'x' || yollar[6].isim == 'x') {
 			line(160, 20, 160, 50); 
 			line(160, 50, 150, 40); //sol ok cizgisi  
 			line(160, 50, 170, 40); //sag ok cizgisi
		}
		else{
			line(160, 20, 160, 50); 
			line(160, 20, 150, 30); //sol ok cizgisi  
			line(160, 20, 170, 30); //sag ok cizgisi
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
  		
		//y yolunun okunu yazdirma
    	if(yollar[5].isim == 'y' || yollar[6].isim == 'y') {
    		line(290, 150, 260, 150); 
    		line(260, 150, 270, 140); //ust ok cizgisi
    		line(260, 150, 270, 160); //alt ok cizgisi
		}
		else{
			line(290, 150, 260, 150);
			line(290, 150, 280, 140); //ust ok cizgisi
			line(290, 150, 280, 160); //alt ok cizgisi
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
  		
		//z yolunun okunu yazdirma
    	if(yollar[5].isim == 'z' || yollar[6].isim == 'z') {
    		line(160, 250, 160, 280);
			line(160, 250, 150, 260); //sol ok cizgisi
			line(160, 250, 170, 260); //sag ok cizgisi
		}
		else{
			line(160, 250, 160, 280);
			line(160, 280, 150, 270); //sol ok cizgisi
			line(160, 280, 170, 270); //sag ok cizgisi
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
  		
		//t yolunun okunu yazdirma
    	if(yollar[5].isim == 't' || yollar[6].isim == 't') {
    		line(30, 150, 60, 150);
    		line(60, 150, 50, 140); //ust ok cizgisi
   			line(60, 150, 50, 160); //alt ok cizgisi
		}
		else{
			line(30, 150, 60, 150);
			line(30, 150, 40, 140); //ust ok cizgisi
			line(30, 150, 40, 160); //alt ok cizgisi
		}
		
		delay(salise);
		cleardevice();
		hareketliYonlerIcinMap(haritaSecim);
		
		//***********************TUM YONLERI AYNI ANDA YAZDIRMA BASLANGIC*****************
    	//a yolunun okunu yazdirma
    	if(yollar[0].git.yon == 'x') {
    		arc(155, 140, 110, 160, 60); 
    		line(135, 84, 125, 80); // ust ok cizgisi 
    		line(135, 84, 125, 94); // alt ok cizgisi 
		}
		else{
			arc(155, 140, 110, 160, 60);               
			line(99, 120, 109, 110); // sag ok cizgisi  
    		line(99, 120, 95, 110); // sol ok cizgisi  
		}
		//b yolunun okunu yazdirma
    	if(yollar[1].git.yon == 'x') {
    		arc(165, 140, 20, 70, 60);
    		line(183, 83, 193, 78); // ust ok cizgisi 
    		line(183, 83, 193, 93); // alt ok cizgisi   
		}
		else{
    		arc(165, 140, 20, 70, 60);  
			line(222, 120, 227, 110); // sag ok cizgisi   
    		line(222, 120, 207, 110); // sol ok cizgisi  
		}
		//c yolunun okunu yazdirma
    	if(yollar[2].git.yon == 't') {
    		arc(155, 160, 200, 250, 60);  					
    		line(100, 180, 110, 190); // sag ok cizgisi 
    		line(100, 180, 95, 190); // sol ok cizgisi 
		}
		else{
			arc(155,160,200,250,60); 
			line(135,215,125,205);  //ust ok cizgisi 
    		line(135,215,125,220);  // alt ok cizgisi 	
		}
		//d yolunun okunu yazdirma
    	if(yollar[3].git.yon == 'y') {
   			arc(165, 160, 290, 340, 60);			
    		line(220, 178, 210, 188); // sol ok cizgisi 
    		line(220, 178, 225, 188); // sag ok cizgisi  
		}
		else{
    		arc(165,160,290,340,60);
			line(185,215,195,205); // ust ok cizgisi   	
    		line(185,215,195,220);  // alt ok cizgisi  
		}
		//e yolunun okunu yazdirma
    	if(yollar[4].git.yon == 't') {
   			line(135, 150, 180, 150);
   			line(135, 150, 145, 140); //ust ok cizgisi
   			line(135, 150, 145, 160); //alt ok cizgisi
		}
		else{
    		line(135, 150, 180, 150);
    		line(180, 150, 170, 140); //ust ok cizgisi
   			line(180, 150, 170, 160); //alt ok cizgisi 
		}
		//x yolunun okunu yazdirma
    	if(yollar[5].isim == 'x' || yollar[6].isim == 'x') {
 			line(160, 20, 160, 50); 
 			line(160, 50, 150, 40); //sol ok cizgisi 
 			line(160, 50, 170, 40); //sag ok cizgisi
		}
		else{
			line(160, 20, 160, 50); 
			line(160, 20, 150, 30); //sol ok cizgisi  
			line(160, 20, 170, 30); //sag ok cizgisi
		}
		//y yolunun okunu yazdirma
    	if(yollar[5].isim == 'y' || yollar[6].isim == 'y') {
    		line(290, 150, 260, 150); 
    		line(260, 150, 270, 140); //ust ok cizgisi
    		line(260, 150, 270, 160); //alt ok cizgisi
		}
		else{
			line(290, 150, 260, 150);
			line(290, 150, 280, 140); //ust ok cizgisi
			line(290, 150, 280, 160); //alt ok cizgisi
		}
		//z yolunun okunu yazdirma
    	if(yollar[5].isim == 'z' || yollar[6].isim == 'z') {
    		line(160, 250, 160, 280);
			line(160, 250, 150, 260); //sol ok cizgisi
			line(160, 250, 170, 260); //sag ok cizgisi
		}
		else{
			line(160, 250, 160, 280);
			line(160, 280, 150, 270); //sol ok cizgisi
			line(160, 280, 170, 270); //sag ok cizgisi
		}
		//t yolunun okunu yazdirma
    	if(yollar[5].isim == 't' || yollar[6].isim == 't') {
    		line(30, 150, 60, 150);
    		line(60, 150, 50, 140); //ust ok cizgisi
   			line(60, 150, 50, 160); //alt ok cizgisi
		}
		else{
			line(30, 150, 60, 150);
			line(30, 150, 40, 140); //ust ok cizgisi
			line(30, 150, 40, 160); //alt ok cizgisi
		}
		
		setcolor(12);
		setbkcolor(WHITE);
		settextstyle(3, HORIZ_DIR, 2);
		outtextxy(50,350,"Tum yonler gosterildi. Cikmak icin enter a basin.");
		
		getch();
		closegraph();
		//*********************TUM YONLERI AYNI ANDA YAZDIRMA SON************************
	}
}

int kullaniciHaritaGirisi() {
	int secim = 0;
	
	printf("Lutfen 1. ya da 2. haritayi seciniz: ");
	scanf("%d", &secim);
	
	while(!(secim == 1 || secim == 2)){
		printf("\nHatali giris! Lutfen 1. ya da 2. haritayi seciniz: ");
		scanf("%d", &secim);
	}
	
	printf("\n");
	
	return secim;
}

void girisSecimi(int haritaSecim){
	char girisler[6],cikislar[6];
	int i, j, boslukSayisi=0;
   
	printf("Iki giris yolu girin (Yollar arasinda bosluk birakin): ");
	fgets(girisler,600,stdin);
   
	while(boslukSayisi!=1){
		for(i=0;i<strlen(girisler);i++){
			if(isblank(girisler[i]))
				boslukSayisi++;
		}
    
		if(boslukSayisi>1){
			printf("\nFazla giris girdiniz. Tekrar girisleri girin: ");
			fgets(girisler,600,stdin);
		}
       	else if(boslukSayisi<1){
			printf("\nEksik giris girdiniz. Tekrar girisleri girin: ");
          	fgets(girisler,600,stdin);
		}
		if(boslukSayisi==1){
			boslukSayisi=0;
			break;
		}
        
		boslukSayisi=0;
    }
	
	printf("Iki cikis yolu girin (Yollar arasinda bosluk birakin): ");
	fgets(cikislar,600,stdin);
    
	while(boslukSayisi!=1){
		for(i=0;i<strlen(cikislar);i++){
			if(isblank(cikislar[i]))
				boslukSayisi++;
		}
		
		if(boslukSayisi>1){
			printf("\nFazla cikis girdiniz. Tekrar cikislari girin: ");
			fgets(cikislar,600,stdin);
		}
		else if(boslukSayisi<1){
			printf("\nEksik cikis girdiniz. Tekrar cikislari girin: ");
			fgets(cikislar,600,stdin);
		}

		if(boslukSayisi==1){
			boslukSayisi=0;
			break;
		}
		boslukSayisi=0;
	}
	
	
	if(haritaSecim==1){
		j=4;
		for(i=0;i<3;i+=2){
        	yollar[j].isim = girisler[i];
        	j++;
    	}
    	
		j=6;
		for(i=0;i<3;i+=2){
      		yollar[j].isim = cikislar[i];
        	j++;
    	}
	}
	
	else if(haritaSecim==2){
		j=5;
    	for(i=0;i<3;i+=2){
        	yollar[j].isim = girisler[i];
        	j++;
    	}
    	
		j=7;
		for(i=0;i<3;i+=2){
       		yollar[j].isim = cikislar[i];
        	j++;
    	}
	}
}

void yonsecimi(int haritaSecim){
    int i,k;
	char j = 'a';
	char degisken = ' ';

	if(haritaSecim == 1) {
		for(i=0; i<4; i++) {
			yollar[i].isim = j;
			j++;
		}
	}
	else if(haritaSecim == 2) {
		for(i=0; i<5; i++) {
			yollar[i].isim = j;
			j++;
		}
	}
	
	if(haritaSecim == 1){

		printf("\n\n");
		printf("Harita baslangic yonlerini su sekilde seciniz: \n"
				"\ta icin ;  baslangic noktasi = t, yon = x ya da baslangic noktasi = x, yon = t,\n"
				"\tb icin ;  baslangic noktasi = y, yon = x ya da baslangic noktasi = x, yon = y,\n"
				"\tc icin ;  baslangic noktasi = t, yon = z ya da baslangic noktasi = z, yon = t,\n"
				"\td icin ;  baslangic noktasi = y, yon = z ya da baslangic noktasi = z, yon = y.\n");
		printf("\n\n");
        
		for(k = 0; k < 4; k++) {
		 	printf("%c icin yon belirleyiniz \n", yollar[k].isim);
			printf("\tBaslangic noktasi : ");
			scanf(" %c", &yollar[k].git.baslangicnoktasi);
			printf("\tYon : ");
			scanf(" %c", &yollar[k].git.yon);
			
                	/*yollarin yonleri kontrol*/
            //girise gore
			for(i=4;i<6;i++){		
				
				if(yollar[i].isim == 'x' && yollar[0].git.yon == 'x' && yollar[1].git.yon == 'x') {
            	  	printf("\nYanlis girdiniz, a ya da b yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
					while(!(degisken == 'a' || degisken == 'b')) {
            	  		printf("Yanlis, a ya da b girmelisiniz: ");
						scanf(" %c", &degisken);
					}
					
					if(degisken == 'a') {
						yollar[0].git.yon = 't';
						yollar[0].git.baslangicnoktasi = 'x';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[0].git.yon);
					}
					else if(degisken == 'b') {
						yollar[1].git.yon = 'y';
						yollar[1].git.baslangicnoktasi = 'x';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[1].git.yon);
					}
				}
				
            	else if(yollar[i].isim == 'y' && yollar[1].git.yon == 'y' && yollar[3].git.yon == 'y') {
                	printf("\nYanlis girdiniz, b ya da d yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
            	  	while(!(degisken == 'b' || degisken == 'd')) {
            	  		printf("Yanlis, b ya da d girmelisiniz: ");
						scanf(" %c", &degisken);
					  }
					  
					if(degisken == 'b') {
						yollar[1].git.yon = 'x';
						yollar[1].git.baslangicnoktasi = 't';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[1].git.yon);
					} 
					else if(degisken == 'd') {
						yollar[3].git.yon = 'z';
						yollar[3].git.baslangicnoktasi = 'y';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[3].git.yon);
					}	
				}
				
            	else if(yollar[i].isim == 'z' &&yollar[2].git.yon == 'z' && yollar[3].git.yon == 'z') {
            		printf("\nYanlis girdiniz, c ya da d yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
            	  	while(!(degisken == 'c' || degisken == 'd')) {
            	  		printf("Yanlis, c ya da d girmelisiniz: ");
						scanf(" %c", &degisken);
					  }
					  
					if(degisken == 'c') {
						yollar[2].git.yon = 't';
						yollar[2].git.baslangicnoktasi = 'z';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[2].git.yon);
					}
					else if(degisken == 'd') {
						yollar[3].git.yon = 'y';
						yollar[3].git.baslangicnoktasi = 'z';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[3].git.yon);
					}
				}
				
            	else if(yollar[i].isim == 't' && yollar[0].git.yon == 't' && yollar[2].git.yon == 't') {
            		printf("\nYanlis girdiniz, a ya da c yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
					while(!(degisken == 'a' || degisken == 'c')) {
            	  		printf("Yanlis, a ya da c girmelisiniz: ");
						scanf(" %c", &degisken);
					  }
					  
					if(degisken == 'a') {
						yollar[0].git.yon = 'x';
						yollar[0].git.baslangicnoktasi = 't';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[0].git.yon);
					}
					else if(degisken == 'c') {
						yollar[2].git.yon = 'z';
						yollar[2].git.baslangicnoktasi = 't';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[2].git.yon);
					}
				}        		
    		}
    		
    		//cikisa gore
			for(i=6;i<8;i++){
				
            	if(yollar[i].isim == 'x' && yollar[0].git.yon == 't' && yollar[1].git.yon == 'y') {
            		printf("\nYanlis girdiniz, a ya da b yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  
					while(!(degisken == 'a' || degisken == 'b')) {
            	  			printf("Yanlis, a ya da b girmelisiniz: ");
							scanf(" %c", &degisken);
					}
					
					if(degisken == 'a') {
						yollar[0].git.yon = 'x';
						yollar[0].git.baslangicnoktasi = 't';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[0].git.yon);
					}
					else if(degisken == 'b') {
						yollar[1].git.yon = 'x';
						yollar[1].git.baslangicnoktasi = 'y';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[1].git.yon);
					}
				}
        		
            	else if(yollar[i].isim == 'y' && yollar[1].git.yon == 'x' && yollar[3].git.yon == 'z') {
            		printf("\nYanlis girdiniz, b ya da d yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
            	  	while(!(degisken == 'b' || degisken == 'd')) {
            	  		printf("Yanlis, b ya da d girmelisiniz: ");
						scanf(" %c", &degisken);
					}
					
					if(degisken == 'b') {
						yollar[1].git.yon = 'y';
						yollar[1].git.baslangicnoktasi = 'x';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[1].git.yon);
						}
					else if(degisken == 'd') {
						yollar[3].git.yon = 'y';
						yollar[3].git.baslangicnoktasi = 'z';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[3].git.yon);
					}
				}      			
         		
            	else if(yollar[i].isim == 'z' && yollar[2].git.yon == 't' && yollar[3].git.yon == 'y') {
            		printf("\nYanlis girdiniz, c ya da d yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  
					while(!(degisken == 'c' || degisken == 'd')) {
            	  		printf("yanlis, c ya da d girmelisiniz: ");
						scanf(" %c", &degisken);
					}
					  
					if(degisken == 'c') {
						yollar[2].git.yon = 'z';
						yollar[2].git.baslangicnoktasi = 't';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[2].git.yon);
					}
					else if(degisken == 'd') {
						yollar[3].git.yon = 'z';
						yollar[3].git.baslangicnoktasi = 'y';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[3].git.yon);
					}
				}

            	else if(yollar[i].isim == 't' && yollar[0].git.yon == 'x' && yollar[2].git.yon == 'z') {
            		printf("\nYanlis girdiniz, a ya da c yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  
					while(!(degisken == 'a' || degisken == 'c')) {
            	  		printf("Yanlis, a ya da c girmelisiniz: ");
						scanf(" %c", &degisken);
					}
					
					if(degisken == 'a') {
						yollar[0].git.yon = 't';
						yollar[0].git.baslangicnoktasi = 'x';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[0].git.yon);
					}
					else if(degisken == 'c') {
						yollar[2].git.yon = 't';
						yollar[2].git.baslangicnoktasi = 'z';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[2].git.yon);
					}
				}
   			}
		}

		printf("\nBelirlediginiz yonler : \n");
		for(i= 0; i< 4; i++) {
			printf("\t%c nin baslangic noktasi: %c , yonu : %c \n", yollar[i].isim, yollar[i].git.baslangicnoktasi, yollar[i].git.yon);
		}
	}
	
	if(haritaSecim == 2) {
		
		printf("\n\n");
		printf("Harita baslangic yonlerini su sekilde seciniz: \n"
				"\ta icin ;  baslangic noktasi = t, yon = x ya da baslangic noktasi = x, yon = t,\n"
				"\tb icin ;  baslangic noktasi = y, yon = x ya da baslangic noktasi = x, yon = y,\n"
				"\tc icin ;  baslangic noktasi = t, yon = z ya da baslangic noktasi = z, yon = t,\n"
				"\td icin ;  baslangic noktasi = y, yon = z ya da baslangic noktasi = z, yon = y,\n"
				"\te icin ;  baslangic noktasi = t, yon = y ya da baslangic noktasi = y, yon = t.\n");
		printf("\n\n");

		for(k = 0; k < 5; k++) {
		 	printf("%c icin yon belirleyiniz \n", yollar[k].isim);
			printf("\tBaslangic noktasi : ");
			scanf(" %c", &yollar[k].git.baslangicnoktasi);
			printf("\tYon : ");
			scanf(" %c", &yollar[k].git.yon);
			
                	//yollarin yonleri kontrol
            //girise gore
    		for(i=5;i<7;i++){
        		if(yollar[i].isim == 'x' && yollar[0].git.yon == 'x' && yollar[1].git.yon == 'x'){
          	      	printf("\nYanlis girdiniz, a ya da b yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
					while(!(degisken == 'a' || degisken == 'b')) {
            	  		printf("Yanlis, a ya da b girmelisiniz: ");
						scanf(" %c", &degisken);
					}
					
					if(degisken == 'a') {
						yollar[0].git.yon = 't';
						yollar[0].git.baslangicnoktasi = 'x';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[0].git.yon);
					}
					else if(degisken == 'b') {
						yollar[1].git.yon = 'y';
						yollar[1].git.baslangicnoktasi = 'x';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[1].git.yon);
					}
          	  		
       			}
        		else if(yollar[i].isim == 'y' && yollar[1].git.yon == 'y' && yollar[3].git.yon == 'y' && yollar[4].git.yon == 'y'){
             		printf("\nYanlis girdiniz, b, d ya da e yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
					while(!(degisken == 'b' || degisken == 'd' || degisken == 'e')) {
            	  		printf("Yanlis, b, d ya da e girmelisiniz: ");
						scanf(" %c", &degisken);
					}
					
					if(degisken == 'b') {
						yollar[1].git.yon = 'x';
						yollar[1].git.baslangicnoktasi = 'y';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[1].git.yon);
					}
					else if(degisken == 'd') {
						yollar[3].git.yon = 'z';
						yollar[3].git.baslangicnoktasi = 'y';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[3].git.yon);
					}
					else if(degisken == 'e') {
						yollar[4].git.yon = 't';
						yollar[4].git.baslangicnoktasi = 'y';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[4].git.yon);
					}
        		}
        		
        		else if(yollar[i].isim == 'z' && yollar[2].git.yon == 'z' && yollar[3].git.yon == 'z'){
					printf("\nYanlis girdiniz, c ya da d yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
					while(!(degisken == 'c' || degisken == 'd')) {
            	  		printf("Yanlis, c ya da d girmelisiniz: ");
						scanf(" %c", &degisken);
					}
					
					if(degisken == 'c') {
						yollar[2].git.yon = 't';
						yollar[2].git.baslangicnoktasi = 'z';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[2].git.yon);
					}
					else if(degisken == 'd') {
						yollar[3].git.yon = 'y';
						yollar[3].git.baslangicnoktasi = 'z';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[3].git.yon);
					}
       			}
        		else if(yollar[i].isim == 't' && yollar[0].git.yon == 't' && yollar[2].git.yon == 't' && yollar[4].git.yon == 't'){
           			printf("\nYanlis girdiniz, a, c ya da e yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
					while(!(degisken == 'a' || degisken == 'c' || degisken == 'e')) {
            	  		printf("Yanlis, a, c ya da e girmelisiniz: ");
						scanf(" %c", &degisken);
					}
					
					if(degisken == 'a') {
						yollar[0].git.yon = 'x';
						yollar[0].git.baslangicnoktasi = 't';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[0].git.yon);
					}
					else if(degisken == 'c') {
						yollar[2].git.yon = 'z';
						yollar[2].git.baslangicnoktasi = 't';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[2].git.yon);
					}
					else if(degisken == 'e') {
						yollar[4].git.yon = 'y';
						yollar[4].git.baslangicnoktasi = 't';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[4].git.yon);
					}
        		}
    		}
    		
    		//cikisa göre
			for(i=7;i<9;i++){
        		if(yollar[i].isim == 'x' && yollar[0].git.yon == 't' && yollar[1].git.yon == 'y'){
         	 		printf("\nYanlis girdiniz, a ya da b yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
					while(!(degisken == 'a' || degisken == 'b')) {
            	  		printf("Yanlis, a ya da b girmelisiniz: ");
						scanf(" %c", &degisken);
					}
					
					if(degisken == 'a') {
						yollar[0].git.yon = 'x';
						yollar[0].git.baslangicnoktasi = 't';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[0].git.yon);
					}
					else if(degisken == 'b') {
						yollar[1].git.yon = 'x';
						yollar[1].git.baslangicnoktasi = 'y';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[1].git.yon);
					}
        		}
        		else if(yollar[i].isim == 'y' && yollar[1].git.yon == 'x' && yollar[3].git.yon == 'z' && yollar[4].git.yon == 't'){
            		printf("\nYanlis girdiniz, b, d ya da e yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
					while(!(degisken == 'b' || degisken == 'd' || degisken == 'e')) {
            	  		printf("Yanlis, b, d ya da e girmelisiniz: ");
						scanf(" %c", &degisken);
					}
					
					if(degisken == 'b') {
						yollar[1].git.yon = 'y';
						yollar[1].git.baslangicnoktasi = 'x';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[1].git.yon);
					}
					else if(degisken == 'd') {
						yollar[3].git.yon = 'y';
						yollar[3].git.baslangicnoktasi = 'z';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[3].git.yon);
					}
					else if(degisken == 'e') {
						yollar[4].git.yon = 'y';
						yollar[4].git.baslangicnoktasi = 't';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[4].git.yon);
					}
        		}
				else if(yollar[i].isim == 'z' && yollar[2].git.yon == 't' && yollar[3].git.yon == 'y'){
            		printf("\nYanlis girdiniz, c ya da d yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
					while(!(degisken == 'c' || degisken == 'd')) {
            	  		printf("Yanlis, c ya da d girmelisiniz: ");
						scanf(" %c", &degisken);
					}
					
					if(degisken == 'c') {
						yollar[2].git.yon = 'z';
						yollar[2].git.baslangicnoktasi = 't';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[2].git.yon);
					}
					else if(degisken == 'd') {
						yollar[3].git.yon = 'z';
						yollar[3].git.baslangicnoktasi = 'y';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[3].git.yon);
					}
        		}
				else if(yollar[i].isim == 't' && yollar[0].git.yon == 'x' && yollar[2].git.yon == 'z' && yollar[4].git.yon == 'y'){
            		printf("\nYanlis girdiniz, a, c ya da e yolunun yonunu degistirmelisiniz.\n");
            	  	printf("Hangi yolun yonunu degistirmek istersiniz? :");
            	  	scanf(" %c", &degisken);
            	  	
					while(!(degisken == 'a' || degisken == 'c' || degisken == 'e')) {
            	  		printf("Yanlis, a, c ya da e girmelisiniz: ");
						scanf(" %c", &degisken);
					}
					
					if(degisken == 'a') {
						yollar[0].git.yon = 't';
						yollar[0].git.baslangicnoktasi = 'x';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[0].git.yon);
					}
					else if(degisken == 'c') {
						yollar[2].git.yon = 't';
						yollar[2].git.baslangicnoktasi = 'z';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[2].git.yon);
					}
					else if(degisken == 'e') {
						yollar[4].git.yon = 't';
						yollar[4].git.baslangicnoktasi = 'y';
						printf("%c yolunun yonu %c olarak degistirildi.\n\n", degisken, yollar[4].git.yon);
			
					}
        		}
    		}
		}
		
		printf("\nBelirlediginiz yonler : \n");
		for(i= 0; i<5; i++) {
			printf("\t%c nin baslangic noktasi: %c , yonu : %c \n", yollar[i].isim, yollar[i].git.baslangicnoktasi, yollar[i].git.yon);
		}
	}
}

void OrtAracSayisi(int haritaSecim) {
	int i,sayac=0,sayac2=0;
	
	if(haritaSecim == 1) {
		printf("\nYollar: ");
		
		for(i=0; i<8; i++) {
			printf("%c ", yollar[i].isim);
		}
		printf("\n");
		
		do {
			if(sayac > 5)
			    printf("Eger 5'ten fazla bilinmeyen girerseniz denklem cozulemez.\n");
		    
			for(i=0; i<8; i++) {
			    printf("%c yolu icin arac sayisi giriniz (Bilinmiyorsa -1 girilmeli) : ", yollar[i].isim);
			    scanf("%d", &yollar[i].ortarac);
			    
				if(yollar[i].ortarac == -1)
			        sayac++;
		    }
		    
			if(sayac == 0)
			    printf("En az bir bilinmeyen girmelisiniz.\n");
		}
		while(sayac == 0 || sayac >5);

        printf("\n");
	}

	if(haritaSecim == 2) {
		printf("\nYollar: ");
		
		for(i=0; i<9; i++) {
			printf("%c ", yollar[i].isim);
		}

		printf("\n");

		do {
			if(sayac2 > 5)
			    printf("Eger 5'ten fazla bilinmeyen girerseniz denklem cozulemez.\n");
		    
			for(i=0; i<9; i++) {
			    printf("%c yolu icin arac sayisi giriniz (Bilinmiyorsa -1 girilmeli) : ", yollar[i].isim);
			    scanf("%d", &yollar[i].ortarac);
			    
				if(yollar[i].ortarac == -1)
			        sayac2++;
		    }
		    
		    if(sayac2 == 0)
			    printf("En az bir bilinmeyen girmelisiniz.\n");
		}
		while(sayac2 == 0 || sayac2 >5);
		
		printf("\n");
	}
}

void denklemCikarma(int haritaSecim){
	int i,j=0,a,b,c,g,d,e=0,f=1,bilinmeyenyeri[5],sayac=5,say=1;
	float matris[5][6],toplam[5];
	
	if(haritaSecim == 1){
		printf("\n");
        
		for(i=0 ;i<8; i++){
        	if(yollar[i].ortarac != -1)
        	    printf("Yol : %c, ortalama : %d\n", yollar[i].isim, yollar[i].ortarac);
			else{
			    printf("Yol : %c, ortalama : x%d\n", yollar[i].isim,f);
			    f++;
		    }
		}
		printf("\n\n");
		
    	for(i=0;i<8;i++){					//eger yol bilinmiyorsa
        	if(yollar[i].ortarac == -1){	//bilinmeyen yolun indisini
         	    bilinmeyenyeri[j] = i;		//bir matrise atar
         	       j++;
			}
		}
		
		for(e=0;e<sayac;e++){ 				//katsayilar matrisinin tum elemanlarini
			for(i=0;i<6;i++){				//sifira esitler
				matris[e][i] = 0;
			}
		}
        
		while(say != 0){
        	d=0;
		    say = 0;
		    
			for(i=0;i<sayac;i++)
                toplam[i]=0;
            
            if(yollar[4].ortarac == -1 || yollar[5].ortarac == -1 || yollar[6].ortarac == -1 || yollar[7].ortarac == -1){
				for(j=4;j<6;j++){  				
					for(e=0;e<sayac;e++){
						if(j == bilinmeyenyeri[e]){					//girisler bilinmiyorsa
                            matris[d][e] = 1;						//bilinmeyenin katsayisini 1 yapýyoruz
                            printf("+ x%d",e+1);					//denklemi yazdirma kismi
                            break;
                    	} 
         	        }
                    
					if(matris[d][e] == 0){							//eger katsayisi sifir ise 
                   	     toplam[d]+=yollar[j].ortarac;				//o yol biliniyor demektir ve o yolun 
                   	     printf("+ %d",yollar[j].ortarac);			//ortalama arac sayisini toplam kismina atiyoruz
				    }  
                }
                
                for(j=6;j<8;j++){					
					for(e=0;e<sayac;e++){		
                        if(j == bilinmeyenyeri[e]){					//cikislar bilinmiyorsa
                            matris[d][e] = -1;						//bilinmeyenlerin katsayisini -1 yapiyoruz
                            printf("- x%d",e+1);					//denklemi yazdirma kismi
                            break;
                       }
         	        }  
                    
					if(matris[d][e] == 0){							//eger katsayisi sifir ise
                    	toplam[d]-=yollar[j].ortarac;				//o yol biliniyor demektir ve o yolun
                    	printf("- %d",yollar[j].ortarac);			//ort arac sayisini toplam kismina atiyoruz
					}   
                }
                
				printf(" = 0\n");
                d++;
            }
            else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
                printf("%d + %d + %d + %d = 0\n",yollar[4].ortarac,yollar[5].ortarac,-yollar[6].ortarac,-yollar[7].ortarac);
		        
				if((yollar[4].ortarac + yollar[5].ortarac) != (yollar[6].ortarac + yollar[7].ortarac )) {
			        printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
			        
					for(i=4; i<8; i++) {
				        printf("%c yolu icin arac sayisi giriniz : ", yollar[i].isim);
				        scanf("%d", &yollar[i].ortarac);
			        }
			        
					printf("%d + %d + %d + %d = 0\n",yollar[4].ortarac,yollar[5].ortarac,-yollar[6].ortarac,-yollar[7].ortarac);
	        	}
         	} // DUGUMLERDEKI TOPLAM KONTROLU BITIS
		    
			for(i=4;i<6;i++){	
				if(yollar[i].isim == 'x'){							//x a b dugumu icin x giris ise
         		    if(yollar[0].git.yon == 'x')			
                        b=1;										//a ve b yolunun yonune gore b ve c
                    else											// degiskenlerine katsayiyi atiyoruz.
                        b=-1;
                     
					if(yollar[1].git.yon == 'x')
                        c=1;
                    else
                        c=-1;
         	        
					if(yollar[i].ortarac == -1 || yollar[0].ortarac == -1 || yollar[1].ortarac == -1){
						for(e=0;e<sayac;e++){				
							if(i == bilinmeyenyeri[e]){				//x yolu icin bilinmiyorsa katsayiyi 
                                matris[d][e] = 1;					//1 yapiyoruz
                                printf("+ x%d",e+1);	
                                break;
                            }
         	            }
                        
						if(matris[d][e] == 0){						//biliniyorsa toplam matisine ekliyoruz
                        	toplam[d]+=yollar[i].ortarac;
						    printf("+ %d",yollar[i].ortarac);
					    }

                        for(e=0;e<sayac;e++){			
                        	if(0 == bilinmeyenyeri[e]){				//a bilinmiyorsa 
                                matris[d][e] = b;					//a nin katsayisini yonune gore
                                printf("+ %d.x%d",b,e+1);			//atiyoruz
                                break;
                            }
                        }
                        
						if(matris[d][e] == 0){						//biliniyorsa yonune gore toplam 
                        	toplam[d]+=b*yollar[0].ortarac;			//matrisine ekliyoruz
						    printf("+ %d.%d",b,yollar[0].ortarac);
					    }

                        for(e=0;e<sayac;e++){
                        	if(1 == bilinmeyenyeri[e]){				//b bilinmiyorsa
                                matris[d][e] = c;					//b nin katsayisini yonune gore
                                printf("+ %d.x%d",c,e+1);			//atiyoruz
                                break;
                            }
                        }
                        
						if(matris[d][e] == 0){						//biliniyorsa yonune gore
                    		toplam[d]+=c*yollar[1].ortarac;			//toplam matrisine ekliyoruz
                    	    printf("+ %d.%d",c,yollar[1].ortarac);
					    }
                        
						printf(" =  0\n");
                        d++;
                	}
					else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
                    	printf("%d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[0].ortarac,c*yollar[1].ortarac);
		               
						if(yollar[i].ortarac + b*yollar[0].ortarac + c*yollar[1].ortarac !=0 ) {
			               printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
				           printf("%c yolu icin arac sayisi girin : ", yollar[0].isim);
				           scanf("%d", &yollar[0].ortarac);
				           printf("%c yolu icin arac sayisi girin : ", yollar[1].isim);
				           scanf("%d", &yollar[1].ortarac);
				           printf("%d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[0].ortarac,c*yollar[1].ortarac);
		            	}
	            	} // DUGUMLERDEKI TOPLAM KONTROLU BITIS
			    }
			}

		    for(i=6;i<8;i++){
				if(yollar[i].isim == 'x'){							//x a b dugumu icin  x cikis ise
         			if(yollar[0].git.yon == 'x')					//a ve b yolunun yonune gore b ve c
                        b=1;										// degiskenlerine katsayiyi atiyoruz.
                    else	
                        b=-1;
                    
					if(yollar[1].git.yon == 'x')
                        c=1;
                    else
                        c=-1;
         	        
					if(yollar[i].ortarac == -1 || yollar[0].ortarac == -1 || yollar[1].ortarac == -1){
						for(e=0;e<sayac;e++){
                        	if(i == bilinmeyenyeri[e]){ 			//x yolu icin bilinmiyorsa  
                                matris[d][e] = -1;					//katsayiyi -1 yapýyoruz
                                printf("- x%d",e+1);
                                break;
                           	}
         	            }
                        
						if(matris[d][e] == 0){						//biliniyorsa toplam matisinden cikariyoruz
                            toplam[d]-=yollar[i].ortarac;
						    printf("- %d",yollar[i].ortarac);	
					    }

                        for(e=0;e<sayac;e++){
                            if(0 == bilinmeyenyeri[e]){				//a bilinmiyorsa
                                matris[d][e] = b;					//a nin katsayisini yonune
                                printf("+ %d.x%d",b,e+1);			//gore atiyoruz
                                break;
                           }
                        }
						   
                        if(matris[d][e] == 0){						//biliniyorsa yonune gore 
                            toplam[d]+=b*yollar[0].ortarac;			//toplam matrisine ekliyoruz
						    printf("+ %d.%d",b,yollar[0].ortarac);	
					    }

                        for(e=0;e<sayac;e++){
                            if(1 == bilinmeyenyeri[e]){				//b bilinmiyorsa
                                matris[d][e] = c;					//b nin katsayisini yonune gore
                                printf("+ %d.x%d",c,e+1);			//atiyoruz
                                break;
                            }
                        }
                        
                        if(matris[d][e] == 0){
                    	    toplam[d]+=c*yollar[1].ortarac;			//biliniyorsa yonune gore
                    	    printf("+ %d.%d",c,yollar[1].ortarac);  //toplam matrisine ekliyoruz
					    }
					    
                        printf(" = 0\n");
                        d++;
                    }
					else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
                        printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[0].ortarac,c*yollar[1].ortarac);
		                if(-yollar[i].ortarac + b*yollar[0].ortarac + c*yollar[1].ortarac !=0 ) {
			                printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
				            printf("%c yolu icin arac sayisi girin : ", yollar[0].isim);
				            scanf("%d", &yollar[0].ortarac);
				            printf("%c yolu icin arac sayisi girin : ", yollar[1].isim);
				            scanf("%d", &yollar[1].ortarac);
				            printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[0].ortarac,c*yollar[1].ortarac);
		               	}
	                } // DUGUMLERDEKI TOPLAM KONTROLU BITIS
			    }
			}
            
			for(i=4;i<6;i++){	
				if(yollar[i].isim == 'y'){							// y b d dugumu icin y giris ise
         			if(yollar[1].git.yon == 'y')					//d ve b yolunun yonune gore b ve c
                        b=1;										// degiskenlerine katsayiyi atiyoruz
                    else
                        b=-1;
                    
					if(yollar[3].git.yon == 'y')
                        c=1;
                    else
                        c=-1;
         	        
					if(yollar[i].ortarac == -1 || yollar[1].ortarac == -1 || yollar[3].ortarac == -1){
						for(e=0;e<sayac;e++){
                        	if(i == bilinmeyenyeri[e]){
                                matris[d][e] = 1;					//y yolu icin bilinmiyorsa 
                                printf("+ x%d",e+1);				//katsayiyi 1 yapiyoruz
                                break;
                           }
         	            }
                        
						if(matris[d][e] == 0){
                            toplam[d]+=yollar[i].ortarac;	 		//biliniyorsa toplam matisine ekliyoruz
                    	    printf("+ %d",yollar[i].ortarac);
					    }
                        
						for(e=0;e<sayac;e++){
                            if(1 == bilinmeyenyeri[e]){				//b bilinmiyorsa 
                                matris[d][e] = b;					//b nin katsayisini yonune gore
                                printf("+ %d.x%d",b,e+1);			//atiyoruz
                                break;
                            }
                    	}
                        
						if(matris[d][e] == 0){
                            toplam[d]+=b*yollar[1].ortarac;			//biliniyorsa yonune gore toplam 
						    printf("+ %d.%d",b,yollar[1].ortarac);	//matrisine ekliyoruz
						}
                        
						for(e=0;e<sayac;e++){						//d bilinmiyorsa
                            if(3 == bilinmeyenyeri[e]){				//d nin katsayisini yonune
                                matris[d][e] = c;					//gore atiyoruz
                                printf("+ %d.x%d",c,e+1);
                                break;
                            }
                        }
                        
						if(matris[d][e] == 0){
                            toplam[d]+=c*yollar[3].ortarac;			//biliniyorsa yonune gore toplam 
                            printf("+ %d.%d",c,yollar[3].ortarac);	//matrisine ekliyoruz
					    }
                        
						printf(" = 0\n");
                        d++;
			        }
			        else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
			            printf("%d + %d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[1].ortarac,c*yollar[3].ortarac);
		                
						if(yollar[i].ortarac + b*yollar[1].ortarac + c*yollar[3].ortarac !=0 ) {
			                printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
				            printf("%c yolu icin arac sayisi girin : ", yollar[3].isim);
				            scanf("%d", &yollar[3].ortarac);
				            printf("%d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[1].ortarac,c*yollar[3].ortarac);
		                }
	                } // DUGUMLERDEKI TOPLAM KONTROLU BITIS
	                
			    }
		    }
		    
			for(i=6;i<8;i++){
				if(yollar[i].isim == 'y'){							//y b d dugumu icin y cikis ise
         			if(yollar[1].git.yon == 'y')					//b ve d yolunun yonune gore b ve c
                        b=1;										//degiskenlerine katsayiyi atiyoruz
                    else
                        b=-1;
                    
					if(yollar[3].git.yon == 'y')
                        c=1;
                    else
                        c=-1;
         	    	
					if(yollar[i].ortarac == -1 || yollar[1].ortarac == -1 || yollar[3].ortarac == -1){
						for(e=0;e<sayac;e++){
                        	if(i == bilinmeyenyeri[e]){				//y yolu icin bilinmiyorsa
                            	matris[d][e] = -1;					//katsayiyi -1 yapiyoruz
                            	printf("- x%d",e+1);
                            	break;
                        	}
         	         	}
                     	
						if(matris[d][e] == 0){
                         	toplam[d]-=yollar[i].ortarac;			//biliniyorsa toplam martisinden cikariyoruz
                         	printf("- %d",yollar[i].ortarac);					
					 	}
                     
						for(e=0;e<sayac;e++){
                        	if(1 == bilinmeyenyeri[e]){				//b bilinmiyorsa
                            	matris[d][e] = b;					//b nin katsayisini yonune 
                            	printf("+ %d.x%d",b,e+1);			//gore atiyoruz
                             	break;
                         	}
                     	}
                     	
						if(matris[d][e] == 0){
                         	toplam[d]+=b*yollar[1].ortarac;			//biliniyorsa yonune gore toplam 
                         	printf("+ %d.%d",b,yollar[1].ortarac);	//matrisine ekliyoruz
					 	}
                    	
						for(e=0;e<sayac;e++){						//d bilinmiyorsa
                        	if(3 == bilinmeyenyeri[e]){				//d nin katsayisini yonune
                            	matris[d][e] = c;					//gore atiyoruz
                            	printf("+ %d.x%d",c,e+1);
                            	break;
                       		}
                    	}
                    	
						if(matris[d][e] == 0){
                        	toplam[d]+=c*yollar[3].ortarac;			//biliniyorsa yonune gore toplam 
                        	printf("+ %d.%d",c,yollar[3].ortarac);	//matrisine ekliyoruz
						}
                    
						printf(" = 0\n");
                    	d++;
                 	}
                 	
					else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
                    	printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[1].ortarac,c*yollar[3].ortarac);
		             	
						if(-yollar[i].ortarac + b*yollar[1].ortarac + c*yollar[3].ortarac !=0 ) {
			             	printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
				         	printf("%c yolu icin arac sayisi girin : ", yollar[3].isim);
				         	scanf("%d", &yollar[3].ortarac);
				         	printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[1].ortarac,c*yollar[3].ortarac);
		             	}
	             	} // DUGUMLERDEKI TOPLAM KONTROLU BITIS
		    	}	
			}

			for(i=4;i<6;i++){
				if(yollar[i].isim == 'z'){
         			if(yollar[2].git.yon == 'z')					//z c d dugumune gore z giris ise
                   		b=1;										//c ve d nin yonune gore b ve c
                	else											//degiskenlerine katsayiyi atiyoruz
                    	b=-1;
                	
					if(yollar[3].git.yon == 'z')
                    	c=1;
                	else
                    	c=-1;
					
					if(yollar[i].ortarac == -1 || yollar[2].ortarac == -1 || yollar[3].ortarac == -1){
						for(e=0;e<sayac;e++){
                    		if(i == bilinmeyenyeri[e]){				//z yolu icin bilinmiyorsa
                        		matris[d][e] = 1;					//katsayiyi 1 yapiyoruz
                        		printf("+ x%d",e+1);
                        		break;
                    		}
         	    		}
                    	
						if(matris[d][e] == 0){
                        	toplam[d]+=yollar[i].ortarac;			//biliniyorsa toplam matrisine ekliyoruz
                        	printf("+ %d",yollar[i].ortarac);			
						}
                        
						for(e=0;e<sayac;e++){			
                    		if(2 == bilinmeyenyeri[e]){				//c yolu bilinmiyorsa katsayisini
                        		matris[d][e] = b;					//yonune gore atiyoruz
                       			printf("+ %d.x%d",b,e+1);
                       			break;
                    		}
                 		}
                    	
						if(matris[d][e] == 0){
                        	toplam[d]+=b*yollar[2].ortarac;			//biliniyorsa yonune gore toplam 
                        	printf("+ %d.%d",b,yollar[2].ortarac);	//matrisine ekliyoruz
						}

						for(e=0;e<sayac;e++){
                    		if(3 == bilinmeyenyeri[e]){				//d yolu bilinmiyorsa katsayisini
                       			matris[d][e] = c;					//yonune gore atiyoruz
                       		 	printf("+ %d.x%d",c,e+1);
                        		break;
                    		}
                 		}
                    	
						if(matris[d][e] == 0){
                        	toplam[d]+=c*yollar[3].ortarac;			//biliniyorsa yonune gore toplam 
                        	printf("+ %d.%d",c,yollar[3].ortarac);	//matrisine ekliyoruz
						}
                		
						printf(" = 0\n");
                		d++;
			 		}
			 		
					else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
			 			printf("%d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[3].ortarac);	
						
						if(yollar[i].ortarac + b*yollar[2].ortarac + c*yollar[3].ortarac !=0 ) {
			           		printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
				       		printf("%c yolu icin arac sayisi girin : ", yollar[2].isim);
				       		scanf("%d", &yollar[2].ortarac);
				       		printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[3].ortarac);
		          		}
	           		} // DUGUMLERDEKI TOPLAM KONTROLU BITIS
	           
		   		}
		 	}
		
			for(i=6;i<8;i++){
				if(yollar[i].isim == 'z'){
         			if(yollar[2].git.yon == 'z')					//z c d dugumune gore z cikis ise
                    	b=1;										//c ve d nin yonune gore b ve c
                	else											//degiskenlerine katsayiyi atiyoruz
                    	b=-1;
                
					if(yollar[3].git.yon == 'z')
                    	c=1;
                	else
                    	c=-1;
         			
					if(yollar[i].ortarac == -1 || yollar[2].ortarac == -1 || yollar[3].ortarac == -1){
						for(e=0;e<sayac;e++){
                    		if(i == bilinmeyenyeri[e]){				//z yolu icin bilinmiyorsa
                        		matris[d][e] = -1;					//katsayiyi -1 yapiyoruz
                        		printf("- x%d",e+1);
                        		break;
                    		}
         	    		}
                    	
						if(matris[d][e] == 0){
                        	toplam[d]-=yollar[i].ortarac;			//biliniyorsa toplam matrisinden cikariyoruz
                        	printf("- %d",yollar[i].ortarac);		
						}

						for(e=0;e<sayac;e++){
                    		if(2 == bilinmeyenyeri[e]){				//c yolu bilinmiyorsa katsayisini
                        		matris[d][e] = b;					//yonune gore atiyoruz
                        		printf("+ %d.x%d",b,e+1);
                        		break;
                    		}
                 		}
                    	
						if(matris[d][e] == 0){
                        	toplam[d]+=b*yollar[2].ortarac;			//c biliniyorsa yonune gore toplam 
                        	printf("+ %d.%d",b,yollar[2].ortarac);	//matrisine ekliyoruz
						}

						for(e=0;e<sayac;e++){
                    		if(3 == bilinmeyenyeri[e]){				//d yolu bilinmiyorsa katsayisini
                        		matris[d][e] = c;					//yonune gore atiyoruz
                        		printf("+ %d.x%d",c,e+1);
                        		break;
                    		}
                 		}
                    	
						if(matris[d][e] == 0){
                    		toplam[d]+=c*yollar[3].ortarac;			//biliniyorsa yonune gore toplam 
                        	printf("+ %d.%d",c,yollar[3].ortarac);	//matrisine ekliyoruz
						}					
                		
						printf(" = 0\n");
                		d++;
              		}
              		
					else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
               			printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[3].ortarac);
		           		
						if(-yollar[i].ortarac + b*yollar[2].ortarac + c*yollar[3].ortarac !=0 ) {
			           		printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
				       		printf("%c yolu icin arac sayisi girin : ", yollar[2].isim);
				       		scanf("%d", &yollar[2].ortarac);
				        	printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[3].ortarac);
		          		}
	           		} // DUGUMLERDEKI TOPLAM KONTROLU BITIS
	           
				}
		 	}
		 	
			for(i=4;i<6;i++){
				if(yollar[i].isim == 't'){
         			if(yollar[2].git.yon == 't')					//t a c dugumune gore t giris ise
                    	b=1;										//a ve c nin yonune gore b ve c
                	else											//degiskenlerine katsayiyi atiyoruz
                    	b=-1;
                	
					if(yollar[0].git.yon == 't')
                    	c=1;
                	else
                   		c=-1;

					if(yollar[i].ortarac == -1 || yollar[2].ortarac == -1 || yollar[0].ortarac == -1){
						for(e=0;e<sayac;e++){
                    		if(i == bilinmeyenyeri[e]){  			//t yolu icin bilinmiyorsa
                        		matris[d][e] = 1;					//katsayiyi 1 yapiyoruz
                        		printf("+ x%d",e+1);
                        		break;
                    		}
         	    		}
                    
						if(matris[d][e] == 0){
                        	toplam[d]+=yollar[i].ortarac;			//biliniyorsa toplam matrisine ekliyoruz
                        	printf("+ %d",yollar[i].ortarac);			
						}
                	
						for(e=0;e<sayac;e++){
                    		if(2 == bilinmeyenyeri[e]){  		
                        		matris[d][e] = b;					//c yolu bilinmiyorsa katsayisini
                        		printf("+ %d.x%d",b,e+1);			//yonune gore atiyoruz
                        		break;
                    		}
                		}
                    
						if(matris[d][e] == 0){
                        	toplam[d]+=b*yollar[2].ortarac;			//biliniyorsa yonune gore toplam 
                        	printf("+ %d.%d",b,yollar[2].ortarac);	//matrisine ekliyoruz	
						}
                	
						for(e=0;e<sayac;e++){
                    		if(0 == bilinmeyenyeri[e]){				//a yolu bilinmiyorsa katsayisini
                        		matris[d][e] = c;					//yonune gore atiyoruz
                        		printf("+ %d.x%d",c,e+1);
                        		break;
                    		}
                		}	
                    
						if(matris[d][e] == 0){
                      	  toplam[d]+=c*yollar[0].ortarac;			//biliniyorsa yonune gore toplam 
                     	   printf("+ %d.%d",c,yollar[0].ortarac);	//matrisine ekliyoruz
						}
                	
						printf(" = 0\n\n");
                		d++;
               		}
					else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
                		printf("%d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[0].ortarac);
		           	
						if( yollar[i].ortarac + b*yollar[2].ortarac + c*yollar[0].ortarac != 0) {
			        		printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
			         	  	printf("%c yolu icin arac sayisi girin : ", yollar[i].isim);
				      	 	scanf("%d", &yollar[i].ortarac);
				    	   	printf("%c yolu icin arac sayisi girin : ", yollar[2].isim);
				     	  	scanf("%d", &yollar[2].ortarac);
				    	   	printf("%c yolu icin arac sayisi girin : ", yollar[0].isim);
				    	   	scanf("%d", &yollar[0].ortarac);
				     	  	printf("%d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[0].ortarac);
				    	   	say++;
		          		}
	           		} // DUGUMLERDEKI TOPLAM KONTROLU BITIS
				}
			}
		
			for(i=6;i<8;i++){
				if(yollar[i].isim == 't'){
         			if(yollar[2].git.yon == 't')					//t a c dugumune gore t cikis ise
            	        b=1;										//a ve c nin yonune gore b ve c
              	  	else											//degiskenlerine katsayiyi atiyoruz
              	      	b=-1;
                
					if(yollar[0].git.yon == 't')
                   	 	c=1;
                	else
                    	c=-1;
         		
					if(yollar[i].ortarac == -1 || yollar[2].ortarac == -1 || yollar[0].ortarac == -1){
						for(e=0;e<sayac;e++){
                    		if(i == bilinmeyenyeri[e]){				//t yolu icin bilinmiyorsa
                        		matris[d][e] = -1;					//katsayiyi -1 yapiyoruz
                    	    	printf("- x%d",e+1);
                        		break;
                    		}
         	    		}
                    
						if(matris[d][e] == 0){
                        	toplam[d]-=yollar[i].ortarac;			//biliniyorsa toplam matrisinden cikariyoruz
                        	printf("- %d",yollar[i].ortarac);			
						}
                	
						for(e=0;e<sayac;e++){
                    		if(2 == bilinmeyenyeri[e]){				//c yolu bilinmiyorsa katsayisini
                        		matris[d][e] = b;					//yonune gore atiyoruz
                        		printf("+ %d.x%d",b,e+1);
                        		break;
                    		}
                		}
                    
						if(matris[d][e] == 0){
            	            toplam[d]+=b*yollar[2].ortarac;			//biliniyorsa yonune gore toplam 
                	        printf("+ %d.%d",b,yollar[2].ortarac);	//matrisine ekliyoruz
						}
                	
						for(e=0;e<sayac;e++){
    	                	if(0 == bilinmeyenyeri[e]){				//a yolu bilinmiyorsa katsayisini
        	                	matris[d][e] = c;					//yonune gore atiyoruz
            	            	printf("+ %d.x%d",c,e+1);
                	        	break;
                    		}
                		}	
                    
						if(matris[d][e] == 0){
        	                toplam[d]+=c*yollar[0].ortarac;			//biliniyorsa yonune gore toplam 
            	            printf("+ %d.%d",c,yollar[0].ortarac);	//matrisine ekliyoruz
						}
                	
						printf(" = 0\n\n");
                		d++;
                	}
                	else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
                		printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[0].ortarac);
		           	
						if( -yollar[i].ortarac + b*yollar[2].ortarac + c*yollar[0].ortarac !=0 ) {
				        	printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
			    	       	printf("%c yolu icin arac sayisi girin : ", yollar[i].isim);
				    	   	scanf("%d", &yollar[i].ortarac);
				       		printf("%c yolu icin arac sayisi girin : ", yollar[2].isim);
				       		scanf("%d", &yollar[2].ortarac);
				       		printf("%c yolu icin arac sayisi girin : ", yollar[0].isim);
					       	scanf("%d", &yollar[0].ortarac);
					       	printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[0].ortarac);
					       	say++;
		          		}
	           		} // DUGUMLERDEKI TOPLAM KONTROLU BITIS
				}
			}
		}
	
		int k=0;
		
		for(i=0;i<sayac;i++){				//toplam matrisini, katsayilar matrisimizin
    		matris[i][5]=-toplam[k];		//son sutununa ekliyoruz.
      	  k++;	
		}

		for(i=0;i<sayac;i++){
    		for(j=0;j<6;j++){
     		   	printf("%2.f   ",matris[i][j]);
       	 	}
			printf("\n");
		}	
		
		lineerEselon(matris,5);
	}
	
	else if(haritaSecim == 2){
		printf("\n");
        
		for(i=0 ;i<9; i++){
    		if(yollar[i].ortarac != -1)
        	    printf("Yol : %c, ortalama : %d\n", yollar[i].isim, yollar[i].ortarac);
			else{
			    printf("Yol : %c, ortalama : x%d\n", yollar[i].isim,f);
			    f++;
		    }
		}
		
		for(i=0;i<9;i++){					//eger yol bilinmiyorsa bilinmeyen 
			if(yollar[i].ortarac == -1){	//yolun indisini bir matrise atar
         	    bilinmeyenyeri[j] = i;
         	    j++;
			 }
		}
		
		for(e=0;e<sayac;e++){ 				//katsayilar matrisinin tum 
			for(i=0;i<6;i++){				//elemanlarini sifira esitler
				matris[e][i] = 0;
			}
		}
        
		while(say != 0){
        	d=0;
		    say = 0;
		    
			for(i=0;i<sayac;i++)
            	toplam[i]=0;
            
            if(yollar[5].ortarac == -1 || yollar[6].ortarac == -1 || yollar[7].ortarac == -1 || yollar[8].ortarac == -1){
				for(j=5;j<7;j++){
					for(e=0;e<sayac;e++){		
                    	if(j == bilinmeyenyeri[e]){					//girisler bilinmiyorsa
                            matris[d][e] = 1;						//bilinmeyenin katsayisini 1 yapýyoruz
                            printf("+ x%d",e+1);					//denklemi yazdirma kismi
                            break;
                        } 
         	        }
                    
					if(matris[d][e] == 0){							//eger katsayisi sifir ise 
                   		toplam[d]+=yollar[j].ortarac;				//o yol biliniyor demektir ve o yolun 
                   	    printf("+ %d",yollar[j].ortarac);			//ort arac sayisini toplam kismina atiyoruz
				    }    
                }
                
				for(j=7;j<9;j++){
					for(e=0;e<sayac;e++){
                        if(j == bilinmeyenyeri[e]){					//cikislar bilinmiyorsa
                            matris[d][e] = -1;						//bilinmeyenlerin katsayisini -1 yapiyoruz
                            printf("- x%d",e+1);
                            break;
                       }
         	        }  
                    
					if(matris[d][e] == 0){							//eger katsayisi sifir ise
                    	toplam[d]-=yollar[j].ortarac;				//o yol biliniyor demektir ve o yolun
                    	printf("- %d",yollar[j].ortarac);			//ort arac sayisini toplam kismina atiyoruz
					}        
                }
				printf(" = 0\n");
                d++;
            }
            else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
                printf("%d + %d + %d + %d = 0\n",yollar[5].ortarac,yollar[6].ortarac,-yollar[7].ortarac,-yollar[8].ortarac);
		        
				if((yollar[5].ortarac + yollar[6].ortarac) != (yollar[7].ortarac + yollar[8].ortarac )) {
			        printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
			    
				    for(i=5; i<9; i++) {
				        printf("%c yolu icin arac sayisi girin : ", yollar[i].isim);
				        scanf("%d", &yollar[i].ortarac);
			        }
			    
				    printf("%d + %d + %d + %d = 0\n",yollar[5].ortarac,yollar[6].ortarac,-yollar[7].ortarac,-yollar[8].ortarac);
	        	}
         	} // DUGUMLERDEKI TOPLAM KONTROLU BITIS
		    
			for(i=5;i<7;i++){
				if(yollar[i].isim == 'x'){							//x a b dugumu icin x giris ise
         			if(yollar[0].git.yon == 'x')
                        b=1;										//a ve b yolunun yonune gore b ve c
                    else											// degiskenlerine katsayiyi atiyoruz.
                        b=-1;
                
				    if(yollar[1].git.yon == 'x')
                         c=1;
                     else
                         c=-1;
					
					if(yollar[i].ortarac == -1 || yollar[0].ortarac == -1 || yollar[1].ortarac == -1){
						for(e=0;e<sayac;e++){
                            if(i == bilinmeyenyeri[e]){				//x yolu icin bilinmiyorsa katsayiyi 
                                matris[d][e] = 1;					//1 yapiyoruz
                                printf("+ x%d",e+1);
                                break;
                            }
         	            }
                        if(matris[d][e] == 0){						//biliniyorsa toplam matisine ekliyoruz
                                toplam[d]+=yollar[i].ortarac;
						        printf("+ %d",yollar[i].ortarac);
					    }

                        for(e=0;e<sayac;e++){
                            if(0 == bilinmeyenyeri[e]){				//a bilinmiyorsa 
                                matris[d][e] = b;					//a nin katsayisini yonune gore
                                printf("+ %d.x%d",b,e+1);			//atiyoruz
                                break;
                            }
                        }
                        
						if(matris[d][e] == 0){						//biliniyorsa yonune gore toplam 
                        	toplam[d]+=b*yollar[0].ortarac;			//matrisine ekliyoruz
						    printf("+ %d.%d",b,yollar[0].ortarac);
					    }

                        for(e=0;e<sayac;e++){
                            if(1 == bilinmeyenyeri[e]){				//b bilinmiyorsa
                                matris[d][e] = c;					//b nin katsayisini yonune gore
                                printf("+ %d.x%d",c,e+1);			//atiyoruz
                                break;
                            }
                    	}
                        if(matris[d][e] == 0){						//biliniyorsa yonune gore
                    		toplam[d]+=c*yollar[1].ortarac;			//toplam matrisine ekliyoruz
                    	    printf("+ %d.%d",c,yollar[1].ortarac);
					    }
                        
						printf(" =  0\n");
                        d++;
                   }
					else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
                    	printf("%d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[0].ortarac,c*yollar[1].ortarac);
						
						if(yollar[i].ortarac + b*yollar[0].ortarac + c*yollar[1].ortarac !=0 ) {
			            	printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
				           	printf("%c yolu icin arac sayisi girin : ", yollar[0].isim);
				           	scanf("%d", &yollar[0].ortarac);
				           	printf("%c yolu icin arac sayisi girin : ", yollar[1].isim);
				           	scanf("%d", &yollar[1].ortarac);
				           	printf("%d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[0].ortarac,c*yollar[1].ortarac);
		               	}
	               	} // DUGUMLERDEKI TOPLAM KONTROLU BITIS
			    }
			}

		    for(i=7;i<9;i++){
				if(yollar[i].isim == 'x'){							//x a b dugumu icin  x cikis ise
         			if(yollar[0].git.yon == 'x')					//a ve b yolunun yonune gore b ve c
                        b=1;										// degiskenlerine katsayiyi atiyoruz.
                    else
                        b=-1;
                    
					if(yollar[1].git.yon == 'x')
                        c=1;
                    else
                        c=-1;
    
					if(yollar[i].ortarac == -1 || yollar[0].ortarac == -1 || yollar[1].ortarac == -1){
						for(e=0;e<sayac;e++){
                            if(i == bilinmeyenyeri[e]){				//x yolu icin bilinmiyorsa  
                                matris[d][e] = -1;					//katsayiyi -1 yapýyoruz
                                printf("- x%d",e+1);
                                break;
                           }
         	            }
                        
						if(matris[d][e] == 0){						//biliniyorsa toplam matisinden cikariyoruz
                            toplam[d]-=yollar[i].ortarac;
						    printf("- %d",yollar[i].ortarac);	
					    }

                        for(e=0;e<sayac;e++){
                            if(0 == bilinmeyenyeri[e]){				//a bilinmiyorsa
                                matris[d][e] = b;					//a nin katsayisini yonune
                                printf("+ %d.x%d",b,e+1);			//gore atiyoruz
                                break;
                           }
                        }   
                        
						if(matris[d][e] == 0){						//biliniyorsa yonune gore 
                            toplam[d]+=b*yollar[0].ortarac;			//toplam matrisine ekliyoruz
						    printf("+ %d.%d",b,yollar[0].ortarac);	
					    }

                        for(e=0;e<sayac;e++){
                            if(1 == bilinmeyenyeri[e]){				//b bilinmiyorsa
                                matris[d][e] = c;					//b nin katsayisini yonune gore
                                printf("+ %d.x%d",c,e+1);			//atiyoruz
                                break;
                            }
                        }
                        
						if(matris[d][e] == 0){
                    	    toplam[d]+=c*yollar[1].ortarac;			//biliniyorsa yonune gore
                    	    printf("+ %d.%d",c,yollar[1].ortarac);  //toplam matrisine ekliyoruz
					    }
                        printf(" = 0\n");
                        d++;
                    }
					else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
                         printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[0].ortarac,c*yollar[1].ortarac);
		            	
						if(-yollar[i].ortarac + b*yollar[0].ortarac + c*yollar[1].ortarac !=0 ) {
			           	    printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
				            printf("%c yolu icin arac sayisi girin : ", yollar[0].isim);
				            scanf("%d", &yollar[0].ortarac);
				            printf("%c yolu icin arac sayisi girin : ", yollar[1].isim);
				            scanf("%d", &yollar[1].ortarac);
				            printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[0].ortarac,c*yollar[1].ortarac);
		                }
	                } // DUGUMLERDEKI TOPLAM KONTROLU BITIS
			    }
		    }
            
			for(i=5;i<7;i++){
				if(yollar[i].isim == 'y'){							// y b d e dugumu icin y giris ise
         			if(yollar[1].git.yon == 'y')					//d b ve e yolunun yonune gore b c g
                    	b=1;										// degiskenlerine katsayiyi atiyoruz
                    else
                        b=-1;
                    
					if(yollar[3].git.yon == 'y')
                        c=1;
                    else
                        c=-1;
                    
					if(yollar[4].git.yon == 'y')
                        g=1;
                    else
                        g=-1;
         	    
					if(yollar[i].ortarac == -1 || yollar[1].ortarac == -1 || yollar[3].ortarac == -1 || yollar[4].ortarac == -1){
						for(e=0;e<sayac;e++){
                            if(i == bilinmeyenyeri[e]){
                                matris[d][e] = 1;					//y yolu icin bilinmiyorsa 
                                printf("+ x%d",e+1);				//katsayiyi 1 yapiyoruz
                                break;
                           	}
         	            }
                        
						if(matris[d][e] == 0){
                            toplam[d]+=yollar[i].ortarac;	 		//biliniyorsa toplam matisine ekliyoruz	
                    	    printf("+ %d",yollar[i].ortarac);
					    }
                        
						for(e=0;e<sayac;e++){
                            if(1 == bilinmeyenyeri[e]){				//b bilinmiyorsa 
                                matris[d][e] = b;					//b nin katsayisini yonune gore
                                printf("+ %d.x%d",b,e+1);			//atiyoruz
                                break;
                            }
                        }
                        
						if(matris[d][e] == 0){
                            toplam[d]+=b*yollar[1].ortarac;			//biliniyorsa yonune gore toplam 
						    printf("+ %d.%d",b,yollar[1].ortarac);	//matrisine ekliyoruz
					    }
                        
						for(e=0;e<sayac;e++){						//d bilinmiyorsa
                            if(3 == bilinmeyenyeri[e]){				//d nin katsayisini yonune
                                matris[d][e] = c;					//gore atiyoruz
                                printf("+ %d.x%d",c,e+1);
                                break;
                            }
                        }
                        
						if(matris[d][e] == 0){						//biliniyorsa yonune gore toplam 
                            toplam[d]+=c*yollar[3].ortarac;			//matrisine ekliyoruz
                            printf("+ %d.%d",c,yollar[3].ortarac);	
					    }
                        
						for(e=0;e<sayac;e++){						//e bilinmiyorsa
                            if(4 == bilinmeyenyeri[e]){				//e nin katsayisini yonune
                                matris[d][e] = g;					//gore atiyoruz
                                printf("+ %d.x%d",g,e+1);
                                break;
                            }
                        } 
                        
						if(matris[d][e] == 0){
                            toplam[d]+=g*yollar[4].ortarac;			//biliniyorsa yonune gore toplam 
                            printf("+ %d.%d",g,yollar[4].ortarac);	//matrisine ekliyoruz
					    }
                        
						printf(" = 0\n");
                        d++;
			        }
			        else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
			            printf("%d + %d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[1].ortarac,c*yollar[3].ortarac,g*yollar[4].ortarac);
		                
						if(yollar[i].ortarac + b*yollar[1].ortarac + c*yollar[3].ortarac +g*yollar[4].ortarac !=0 ) {
			                printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
				            printf("%c yolu icin arac sayisi girin : ", yollar[3].isim);
				            scanf("%d", &yollar[3].ortarac);
				            printf("%c yolu icin arac sayisi girin : ", yollar[4].isim);
				            scanf("%d", &yollar[4].ortarac);
				            printf("%d + %d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[1].ortarac,c*yollar[3].ortarac,g*yollar[4].ortarac);
		                }
	                } // DUGUMLERDEKI TOPLAM KONTROLU BITIS
	        	}
		    }
		    
			for(i=7;i<9;i++){
				if(yollar[i].isim == 'y'){							//y b d e dugumu icin y cikis ise
         		    if(yollar[1].git.yon == 'y')					//b d e yolunun yonune gore b c g
                        b=1;										//degiskenlerine katsayiyi atiyoruz
                    else
                        b=-1;
            
			        if(yollar[3].git.yon == 'y')
                        c=1;
                    else
                        c=-1;
            
			        if(yollar[4].git.yon == 'y')
                        g=1;
                    else
                        g=-1;
         		    
					if(yollar[i].ortarac == -1 || yollar[1].ortarac == -1 || yollar[3].ortarac == -1 || yollar[4].ortarac == -1){
						for(e=0;e<sayac;e++){
                        	if(i == bilinmeyenyeri[e]){				//y yolu icin bilinmiyorsa
                            	matris[d][e] = -1;					//katsayiyi -1 yapiyoruz
                            	printf("- x%d",e+1);
                           		break;
                        	}
         	         	}

						if(matris[d][e] == 0){
                        	toplam[d]-=yollar[i].ortarac;			//biliniyorsa toplam martisinden cikariyoruz
                        	printf("- %d",yollar[i].ortarac);	
					 	}
                     	
						for(e=0;e<sayac;e++){
                        	if(1 == bilinmeyenyeri[e]){				//b bilinmiyorsa
                            	matris[d][e] = b;					//b nin katsayisini yonune 
                            	printf("+ %d.x%d",b,e+1);			//gore atiyoruz
                             	break;
                         	}
                     	}
                     	
						if(matris[d][e] == 0){
                      		toplam[d]+=b*yollar[1].ortarac;			//biliniyorsa yonune gore toplam 
                        	printf("+ %d.%d",b,yollar[1].ortarac);	//matrisine ekliyoruz
					 	}
                    	
						for(e=0;e<sayac;e++){						//d bilinmiyorsa
                        	if(3 == bilinmeyenyeri[e]){				//d nin katsayisini yonune
                            	matris[d][e] = c;					//gore atiyoruz
                            	printf("+ %d.x%d",c,e+1);
                     	    	break;
                     	   	}
                    	}
                    	
						if(matris[d][e] == 0){
                        	toplam[d]+=c*yollar[3].ortarac;			//biliniyorsa yonune gore toplam 
                        	printf("+ %d.%d",c,yollar[3].ortarac);	//matrisine ekliyoruz	
						}
						
                    	for(e=0;e<sayac;e++){						//e bilinmiyorsa
                        	if(4 == bilinmeyenyeri[e]){				//e nin katsayisini yonune
                            	matris[d][e] = g;					//gore atiyoruz
                            	printf("+ %d.x%d",g,e+1);
                            	break;
                        	}
                    	}
                    	
						if(matris[d][e] == 0){
                        	toplam[d]+=g*yollar[4].ortarac;			//biliniyorsa yonune gore toplam 
                        	printf("+ %d.%d",g,yollar[4].ortarac);	//matrisine ekliyoruz
						}
                    	
						printf(" = 0\n");
                    	d++;
                 	}
					else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
                     	printf("%d + %d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[1].ortarac,c*yollar[3].ortarac,g*yollar[4].ortarac);
		             	
						if(-yollar[i].ortarac + b*yollar[1].ortarac + c*yollar[3].ortarac +g*yollar[4].ortarac !=0 ) {
			             	printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
				        	printf("%c yolu icin arac sayisi girin : ", yollar[3].isim);
					    	scanf("%d", &yollar[3].ortarac);
					        printf("%c yolu icin arac sayisi girin : ", yollar[4].isim);
					        scanf("%d", &yollar[4].ortarac);
					        printf("%d + %d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[1].ortarac,c*yollar[3].ortarac,g*yollar[4].ortarac);
		             	}
	             	} // DUGUMLERDEKI TOPLAM KONTROLU BITIS
		    	}
			}

			for(i=5;i<7;i++){
				if(yollar[i].isim == 'z'){
         			if(yollar[2].git.yon == 'z')					//z c d dugumune gore z giris ise
                    	b=1;										//c ve d nin yonune gore b ve c
                	else											//degiskenlerine katsayiyi atiyoruz
                    	b=-1;
                
					if(yollar[3].git.yon == 'z')
                    	c=1;
                	else
                    	c=-1;
         			
					if(yollar[i].ortarac == -1 || yollar[2].ortarac == -1 || yollar[3].ortarac == -1){
						for(e=0;e<sayac;e++){
                    		if(i == bilinmeyenyeri[e]){				//z yolu icin bilinmiyorsa
                        		matris[d][e] = 1;					//katsayiyi 1 yapiyoruz
                        		printf("+ x%d",e+1);
                       	 		break;
                    		}
         	    		}
                    	
						if(matris[d][e] == 0){
                        	toplam[d]+=yollar[i].ortarac;			//biliniyorsa toplam matrisine ekliyoruz
                       		printf("+ %d",yollar[i].ortarac);	
						}
                        
                 		
						for(e=0;e<sayac;e++){
							if(2 == bilinmeyenyeri[e]){				//c yolu bilinmiyorsa katsayisini
                        		matris[d][e] = b;					//yonune gore atiyoruz
                        		printf("+ %d.x%d",b,e+1);
                       		 	break;
                    		}
                 		}
                    	
						if(matris[d][e] == 0){
                        	toplam[d]+=b*yollar[2].ortarac;			//biliniyorsa yonune gore toplam 
                        	printf("+ %d.%d",b,yollar[2].ortarac);	//matrisine ekliyoruz
						}

						for(e=0;e<sayac;e++){
                    		if(3 == bilinmeyenyeri[e]){				//d yolu bilinmiyorsa katsayisini
                        		matris[d][e] = c;					//yonune gore atiyoruz
                        		printf("+ %d.x%d",c,e+1);
                        		break;
                   	 		}
                 		}
                    
						if(matris[d][e] == 0){
                      		toplam[d]+=c*yollar[3].ortarac;			//biliniyorsa yonune gore toplam 
                     	  	printf("+ %d.%d",c,yollar[3].ortarac);	//matrisine ekliyoruz
						}
                		printf(" = 0\n");
                		d++;
			 		}
					else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
			 			printf("%d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[3].ortarac);
		           	
						if(yollar[i].ortarac + b*yollar[2].ortarac + c*yollar[3].ortarac !=0 ) {
			       	 		printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
				       		printf("%c yolu icin arac sayisi girin : ", yollar[2].isim);
				       		scanf("%d", &yollar[2].ortarac);
				       		printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[3].ortarac);
		          		}
	          		}	 // DUGUMLERDEKI TOPLAM KONTROLU BITIS
	       	 	}
			}
		
			for(i=7;i<9;i++){
        		if(yollar[i].isim == 'z'){
         			if(yollar[2].git.yon == 'z')					//z c d dugumune gore z cikis ise
            	        b=1;										//c ve d nin yonune gore b ve c
              		else											//degiskenlerine katsayiyi atiyoruz
                    	b=-1;
              	  
					if(yollar[3].git.yon == 'z')
                	    c=1;
                	else
                    	c=-1;
         		
					if(yollar[i].ortarac == -1 || yollar[2].ortarac == -1 || yollar[3].ortarac == -1){
						for(e=0;e<sayac;e++){
                	    	if(i == bilinmeyenyeri[e]){				//z yolu icin bilinmiyorsa
                    		    matris[d][e] = -1;					//katsayiyi -1 yapiyoruz
                    		    printf("- x%d",e+1);
                     		   	break;
                    		}
         	    		}
                    
						if(matris[d][e] == 0){
    	                    toplam[d]-=yollar[i].ortarac;			//biliniyorsa toplam matrisinden cikariyoruz
        	                printf("- %d",yollar[i].ortarac);	
						}
	
						for(e=0;e<sayac;e++){
        	            	if(2 == bilinmeyenyeri[e]){				//c yolu bilinmiyorsa katsayisini
            	            	matris[d][e] = b;					//yonune gore atiyoruz
                	        	printf("+ %d.x%d",b,e+1);
                    	    	break;
                    		}
                		}	
                    
						if(matris[d][e] == 0){
    	                    toplam[d]+=b*yollar[2].ortarac;			//biliniyorsa yonune gore toplam 
        	                printf("+ %d.%d",b,yollar[2].ortarac);	//matrisine ekliyoruz
						}
	
                		for(e=0;e<sayac;e++){
                    		if(3 == bilinmeyenyeri[e]){				//d yolu bilinmiyorsa katsayisini
                        		matris[d][e] = c;					//yonune gore atiyoruz
    	                    	printf("+ %d.x%d",c,e+1);
        	            		break;
            	        	}
                	 	}
	
						if(matris[d][e] == 0){
    	                	toplam[d]+=c*yollar[3].ortarac;			//biliniyorsa yonune gore toplam 
        	                printf("+ %d.%d",c,yollar[3].ortarac);	//matrisine ekliyoruz
						}					
                		printf(" = 0\n");
                		d++;
              		}
					else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
               			printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[3].ortarac);
		           	
						if(-yollar[i].ortarac + b*yollar[2].ortarac + c*yollar[3].ortarac !=0 ) {
				           printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
					       printf("%c yolu icin arac sayisi girin : ", yollar[2].isim);
					       scanf("%d", &yollar[2].ortarac);
					       printf("%d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[3].ortarac);
		          		}
		           	} // DUGUMLERDEKI TOPLAM KONTROLU BITIS 
				}
			}
		
			for(i=5;i<7;i++){
	        	if(yollar[i].isim == 't'){
    	     		if(yollar[2].git.yon == 't')					//t a c e dugumune gore t giris ise
        	            b=1;										//a c e nin yonune gore b c g
            	    else											//degiskenlerine katsayiyi atiyoruz
                	    b=-1;
                
					if(yollar[0].git.yon == 't')
                  	  	c=1;
	                else
    	                c=-1;
                
					if(yollar[4].git.yon == 't')
            	        g=1;
                	else
                    	g=-1;

					if(yollar[i].ortarac == -1 || yollar[2].ortarac == -1 || yollar[0].ortarac == -1 || yollar[4].ortarac == -1){
						for(e=0;e<sayac;e++){
        	            	if(i == bilinmeyenyeri[e]){  			//t yolu icin bilinmiyorsa
            	        	    matris[d][e] = 1;					//katsayiyi 1 yapiyoruz
                	      	  	printf("+ x%d",e+1);
                    	   		break;
                   			}
         	    		}
                    
						if(matris[d][e] == 0){
    	                    toplam[d]+=yollar[i].ortarac;			//biliniyorsa toplam matrisine ekliyoruz
        	                printf("+ %d",yollar[i].ortarac);	
						}
                		
						for(e=0;e<sayac;e++){
    	                	if(2 == bilinmeyenyeri[e]){
        	                	matris[d][e] = b;					//c yolu bilinmiyorsa katsayisini
            	           	 	printf("+ %d.x%d",b,e+1);			//yonune gore atiyoruz
                    	    	break;
                	    	}
                		}
                    	
						if(matris[d][e] == 0){
                    	    toplam[d]+=b*yollar[2].ortarac;			//biliniyorsa yonune gore toplam 
                        	printf("+ %d.%d",b,yollar[2].ortarac);	//matrisine ekliyoruz		
						}
                	
						for(e=0;e<sayac;e++){
                    		if(0 == bilinmeyenyeri[e]){				//a yolu bilinmiyorsa katsayisini
                        		matris[d][e] = c;					//yonune gore atiyoruz
                        		printf("+ %d.x%d",c,e+1);
                        		break;
                    		}
                		}
                    
						if(matris[d][e] == 0){
    	                    toplam[d]+=c*yollar[0].ortarac;			//biliniyorsa yonune gore toplam 
        	                printf("+ %d.%d",c,yollar[0].ortarac);	//matrisine ekliyoruz
						}
            	
						for(e=0;e<sayac;e++){
    	                	if(4 == bilinmeyenyeri[e]){				//e yolu bilinmiyorsa katsayisini
        	                	matris[d][e] = g;					//yonune gore atiyoruz
            	            	printf("+ %d.x%d",g,e+1);
                	        	break;
                    		}
                		}	
                    
						if(matris[d][e] == 0){
    	                    toplam[d]+=g*yollar[4].ortarac;			//biliniyorsa yonune gore toplam 
        	                printf("+ %d.%d",g,yollar[4].ortarac);	//matrisine ekliyoruz
						}
                		printf(" = 0\n\n");
                		d++;
                	}
                	else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
                		printf("%d + %d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[0].ortarac,g*yollar[4].ortarac);
		           	
						if( yollar[i].ortarac + b*yollar[2].ortarac + c*yollar[0].ortarac +g*yollar[4].ortarac !=0 ) {
			        		printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
			        	   	printf("%c yolu icin arac sayisi girin : ", yollar[i].isim);
					       	scanf("%d", &yollar[i].ortarac);
					       	printf("%c yolu icin arac sayisi girin : ", yollar[2].isim);
					       	scanf("%d", &yollar[2].ortarac);
					       	printf("%c yolu icin arac sayisi girin : ", yollar[0].isim);
					       	scanf("%d", &yollar[0].ortarac);
					       	printf("%c yolu icin arac sayisi girin : ", yollar[4].isim);
					      	scanf("%d", &yollar[4].ortarac);
					        printf("%d + %d + %d + %d = 0\n",yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[0].ortarac,g*yollar[4].ortarac);
					        say++;
			           	}
	   	        	} // DUGUMLERDEKI TOPLAM KONTROLU BITIS
				}
			}
		
			for(i=7;i<9;i++){
				if(yollar[i].isim == 't'){
         			if(yollar[2].git.yon == 't')					//t a c e dugumune gore t cikis ise
                    	b=1;										//a c e nin yonune gore b ve c
	                else											//degiskenlerine katsayiyi atiyoruz
    	                b=-1;
        	        
					if(yollar[0].git.yon == 't')
    	                c=1;
        	        else
            	        c=-1;
                	
					if(yollar[4].git.yon == 't')
    	                g=1;
        	        else
            	        g=-1;
        	
					if(yollar[i].ortarac == -1 || yollar[2].ortarac == -1 || yollar[0].ortarac == -1 || yollar[4].ortarac == -1){
						for(e=0;e<sayac;e++){
        	            	if(i == bilinmeyenyeri[e]){				//t yolu icin bilinmiyorsa
            	    	        matris[d][e] = -1;					//katsayiyi -1 yapiyoruz
                	    	    printf("- x%d",e+1);
                    	    	break;
                    		}
         	    		}
                    
						if(matris[d][e] == 0){
    	                    toplam[d]-=yollar[i].ortarac;			//biliniyorsa toplam matrisinden cikariyoruz
        	                printf("- %d",yollar[i].ortarac);	
						}
                	
						for(e=0;e<sayac;e++){
    	                	if(2 == bilinmeyenyeri[e]){				//c yolu bilinmiyorsa katsayisini
        	                	matris[d][e] = b;					//yonune gore atiyoruz
            	            	printf("+ %d.x%d",b,e+1);
                	    	    break;
                    		}
                		}
                    
						if(matris[d][e] == 0){
    	                    toplam[d]+=b*yollar[2].ortarac; 		//biliniyorsa yonune gore toplam 
        	                printf("+ %d.%d",b,yollar[2].ortarac);	//matrisine ekliyoruz	
						}
                	
						for(e=0;e<sayac;e++){
    	                	if(0 == bilinmeyenyeri[e]){ 			//a yolu bilinmiyorsa katsayisini
        	                	matris[d][e] = c;					//yonune gore atiyoruz
            	            	printf("+ %d.x%d",c,e+1);
                	        	break;
                    		}
                		}	
                    
						if(matris[d][e] == 0){ 
    	                    toplam[d]+=c*yollar[0].ortarac; 		//biliniyorsa yonune gore toplam 
        	                printf("+ %d.%d",c,yollar[0].ortarac);	//matrisine ekliyoruz	
						}
                	
						for(e=0;e<sayac;e++){
    	                	if(4 == bilinmeyenyeri[e]){ 			//e yolu bilinmiyorsa katsayisini
        	                	matris[d][e] = g;					//yonune gore atiyoruz
           		             	printf("+ %d.x%d",g,e+1);
           	   		          	break;
                   		 	}
                		}
                    
						if(matris[d][e] == 0){
    	                    toplam[d]+=g*yollar[4].ortarac; 		//biliniyorsa yonune gore toplam
        	                printf("+ %d.%d",g,yollar[4].ortarac);	//matrisine ekliyoruz	
						}
                		printf(" = 0\n\n");
                		d++;
                	}	
        	        else { // DUGUMLERDEKI TOPLAM KONTROLU BASLANGIC
            	    	printf("%d + %d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[0].ortarac,g*yollar[4].ortarac);
					
						if( -yollar[i].ortarac + b*yollar[2].ortarac + c*yollar[0].ortarac +g*yollar[4].ortarac !=0 ) {
				        	printf("Girisler ve cikislarin toplami birbirine esit olmali\n");
				        	printf("%c yolu icin arac sayisi girin : ", yollar[i].isim);
					       	scanf("%d", &yollar[i].ortarac);
					       	printf("%c yolu icin arac sayisi girin : ", yollar[2].isim);
				    	    scanf("%d", &yollar[2].ortarac);
				        	printf("%c yolu icin arac sayisi girin : ", yollar[0].isim);
				        	scanf("%d", &yollar[0].ortarac);
				     	   printf("%c yolu icin arac sayisi girin : ", yollar[4].isim);
				  	      scanf("%d", &yollar[4].ortarac);
					        printf("%d + %d + %d + %d = 0\n",-yollar[i].ortarac,b*yollar[2].ortarac,c*yollar[0].ortarac,g*yollar[4].ortarac);
					        say++;
		    	      	}
	           		} // DUGUMLERDEKI TOPLAM KONTROLU BITIS   
				}
			}
		}
	
		int k=0;
	
		for(i=0;i<sayac;i++){				//toplam matrisini, katsayilar matrisimizin
    		matris[i][5]=-toplam[k];		//son sutununa ekliyoruz.
        	k++;
		}

		for(i=0;i<sayac;i++){
    		for(j=0;j<6;j++){
        		printf("%2.f   ",matris[i][j]);
        	}
			printf("\n");
		}	
		lineerEselon(matris,5);
	}
}

void lineerEselon(float matris[][6],int n){
	int i,j,k,a,m=6,array2[n],topbilinmeyen=n,sayac=0;
	float temp1[m],temp2[m],b,c;
	//m = sutun sayisi, n = satir sayisi, topbilinmeyen = toplam bilinmeyen sayisi
	
	//bilinmeyen sayýsýný bulma 
	for(i=0;i<m;i++){      			//Sirayla tum sutunlari gezer. Bir sutun bastan sona kadar 0 ise o sutunun denk geldigi
	    for(j=0;j<n;j++){   		//yerde oyle bir bilinmeyen yok demektir. Ornegin x1 icin 1. sutuna bakalim. 1. sutunun
		    if(matris[j][i] == 0){	//tamami 0 ise x1 bilinen bir degerdir. Bilinmeseydi katsayisi 0'dan farkli olmaliydi.
			    sayac++; 			//eger tum sutun 0'a esitse oyle bir bilinmeyen yoktur ve sayaci artirip bir diziye atar. 
		    }
	    }
		array2[i] = sayac;
	    sayac=0;
    }
    
	for(i=0;i<m;i++){         		//Attigimiz sayac degerleri satir sayisina esitse 
		if(array2[i] == n)	  		//oyle bir bilinmeyen olmadýgýndan toplam bilinmeyen sayisini 
	    	topbilinmeyen--;  		//bir azaltir
    }
    
    for(i=0;i<n;i++){
        for(j=0;j<topbilinmeyen;j++){
            if(i==j && matris[i][j]==0){		//kosegen elemanlarini dolasiyoruz. Eger kosegen elemanlari sifira esitse
                for(a=(n-1);a>i;a--){			//alt satirlardan bir satiri, kosegen elemani sifir olan satirla yer 
                    if(matris[a][j]!=0){		//degistirmek icin o satiri temp1 e kaydediyoruz. 
                        for(k=0;k<m;k++)		
                            temp1[k]=matris[a][k];
                        break;
                    }
                }
                
				for(k=0;k<m;k++)				//Kosegen elemani sifir olan satiri da temp 2 ye kaydediyoruz.
                    temp2[k]=matris[i][k];			
                	
				for(k=0;k<m;k++){				// iki satirin yerini degistirme islemini yapiyoruz.
                    matris[i][k]=temp1[k];
                    matris[a][k]=temp2[k];	
                }
            	printf("\n");
                
				for(a=0;a<n;a++){				//yeni matrisimizi yazdiriyoruz
                    for(k=0;k<m;k++){
                        printf("%5.2f ",matris[a][k]);
                    }
					printf("\n");
                }
                
				if(matris[i][j]!=1 && matris[i][j]!=0){		//eger kosegen elemani sifira ya da bire esit degil ise
                    c=matris[i][j];							//kosegen elemaninin degerini c ye atiyoruz
                
				    for(k=0;k<m;k++){						//ve bu satirin tum elemanlarini c ye boluyoruz
                        matris[i][k]=matris[i][k]/c;
                    }
                    printf("\n");
                    for(a=0;a<n;a++){						//yeni matrisimizi yazdiriyoruz
                    	for(k=0;k<m;k++){
                        	printf("%5.2f ",matris[a][k]);
                        }
						printf("\n");
                    }
                }
                
				for(a=0;a<n;a++){				//kosegen elemanlari disinda
                    if(a!=i){					//ayný sutundaki diger satirdaki elemanlari
                        b=matris[a][j];			//sifirliyoruz.
                
				        for(k=0;k<m;k++)	
                            matris[a][k]=(-1)*b*matris[i][k]+matris[a][k];  
                    }
                }
                printf("\n");
                
				for(a=0;a<n;a++){
                    for(k=0;k<m;k++){
                        printf("%5.2f ",matris[a][k]);
                    }
					printf("\n");
                }
            }
            
            else if(i==j && matris[i][j]!=0){			//eger kosegen elemanlari sifir degil ise
                if(matris[i][j]!=1){					//ve eger kosegen elemanlari bir de degil ise
             		c=matris[i][j];						//matrisin kosegen elemanini c ye atiyoruz.
                    
					for(k=0;k<m;k++){					//o satirin tum elemanlarini c sayisina boluyoruz.
                        matris[i][k]=matris[i][k]/c;
                    }
                    printf("\n");
                    
					for(a=0;a<n;a++){						//yeni matrisimizi yazdiriyoruz
                        for(k=0;k<m;k++){
                            printf("%5.2f ",matris[a][k]);
                        }
						printf("\n");
                    }
                }
                
				for(a=0;a<n;a++){							//kosegen elemanlari disinda
                    if(a!=i){								//ayný sutundaki diger satirdaki elemanlari
                        b=matris[a][j];						//sifirliyoruz.
                
				        for(k=0;k<m;k++)
                            matris[a][k]=(-1)*b*matris[i][k]+matris[a][k];
                    }
                }
                printf("\n");
                
				for(a=0;a<n;a++){
                    for(k=0;k<m;k++){
                        printf("%5.2f ",matris[a][k]);
                    }
					printf("\n");
                }
            }
        }
    }
	
	int t=0,dizi[n][m],dizi2[n],dizi3[n],denklemsay1=n,denklemsay2=n,sayac1=0;
    float dizi4[n][m];
	
	for(i=0;i<n;i++){			
		for(j=0;j<n;j++){			
			if(matris[i][j] != 0){
				dizi[i][t]=j;					//dizi hangi eleman sifir degil ise onu tutuyor. Mesela 
				dizi4[i][t]=matris[i][j];		//2. eleman sifir degilse bilinmiyor demektir. Bu da x2 olur.
				t++;
			}
		}
		dizi2[i]=t;
	 	t=0;
	}
							//dizi4 bilinmeyen elemanin katsayisini (1 ya da -1) tutuyor
	printf("\n");			//dizi bilinmeyen elemani tutuyor
	for(i=0;i<n;i++){		//dizi2 bilinmeyen sayisini tutuyor. bilinmeyen sayisina gore denklemi yazdiriyoruz.
		if(dizi2[i] == 1) {
			printf("%.0f * x%d = %.2f\n",dizi4[i][0],dizi[i][0]+1,matris[i][m-1]);
		}
		else if(dizi2[i] == 2) {
			printf("%.0f * x%d + %.0f * x%d = %.2f\n",dizi4[i][0],dizi[i][0]+1,dizi4[i][1],dizi[i][1]+1,matris[i][m-1]);
		}	
		else if(dizi2[i] == 3) {
   	 		printf("%.0f * x%d + %.0f * x%d + %.0f * x%d = %.2f\n"
				"",dizi4[i][0],dizi[i][0]+1,dizi4[i][1],dizi[i][1]+1,dizi4[i][2],dizi[i][2]+1,matris[i][m-1]);
		}
		else if(dizi2[i] == 4) {
			printf("%.0f * x%d + %.0f * x%d + %.0f * x%d + %.0f * x%d = %.2f\n"
			"",dizi4[i][0],dizi[i][0]+1,dizi4[i][1],dizi[i][1]+1,dizi4[i][2],dizi[i][2]+1,dizi4[i][3],dizi[i][3]+1,matris[1][m-1]);
		}
    	else if(dizi2[i] == 5) {
    		printf("%.0f * x%d + %.0f * x%d + %.0f * x%d + %.0f * x%d +%.0f * x%d= %.2f\n"
			"",dizi4[i][0],dizi[i][0]+1,dizi4[i][1],dizi[i][1]+1,dizi4[i][2],dizi[i][2]+1,dizi4[i][3],dizi[i][3]+1,dizi4[i][4],dizi[i][4]+1,matris[1][m-1]);

		}
	}
	
	//rank hesaplama
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(matris[i][j] == 0){	//tum satirin sifir oldugu 
				sayac1++;			//satir sayisini buluyoruz.
			}
		}
		dizi3[i] = sayac1;
	 	sayac1=0;
	}
	
	for(i=0;i<n;i++){
		if(dizi3[i] == n)			//tum satir sifir degil ise
	    	denklemsay1--;			// denklemsay1 i azaltiyoruz. yani rankini buluyoruz.
	}
									//ustteki bolumde matrisin toplam kismini katamdan yaptýk.
	for(i=0;i<n;i++){				//ayný islemi matrisin toplam kismi dahil oldugu hali de yapiyoruz
		for(j=0;j<m;j++){			
			if(matris[i][j] == 0){	//tum satirin sifir oldugu
				sayac1++;			//satir sayisini buluyoruz.
			}
		}
		dizi3[i] = sayac1;
		sayac1=0;
	}
	
	for(i=0;i<n;i++){				//tum satir sifir degil ise
		if(dizi3[i] == m)			//denklemsay2 yi azaltiyoruz. yani rankini buluyoruz.
	    	denklemsay2--;
	}
	printf("\n");
	
	if(denklemsay1 != denklemsay2)		//eger ranklar birbirine esit degil ise cozum yoktur. 
    	printf("Sistemin cozumu yoktur.\n\n");
	
	else if(denklemsay1 == denklemsay2){		//ranklar birbirine esitse cozum vardir.
		printf("Sistemin cozumu vardir.\n\n");
		
    	if(denklemsay1 == topbilinmeyen){
    	   	printf("Sistemin tek cozumu vardir.\n\n");		//rank toplam bilinmeyene esitse tek cozum vardir
    	   	
			for(i=0; i<denklemsay1; i++) {
				if(matris[i][m-1] < 0) {
    	   			printf("\nBilinmeyen ortalama arac sayilarinda "
						   "negatif oldugundan sistemin su haliyle\ncozumu yoktur. Ancak "
						   "ortalama arac sayisi %.2f olan yolun yonu ters olarak "
						   "alinirsa ; \n\n", matris[i][m-1]);
						   
					printf("x%d = %.2f\n", i+1, -matris[i][m-1]);
				}
				else {
					printf("x%d = %.2f\n", i+1, matris[i][m-1]);
				}	
			}
		}
    	else
        	printf("Sistemin n-r yani %d-%d = %d degiskene bagli"		//aksi halde sonsuz cozum vardir
			" sonsuz cozumu vardir.\n\n",topbilinmeyen,denklemsay1, topbilinmeyen-denklemsay1);	
	}
}

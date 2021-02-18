// LCD baðlantýlarý
sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

char sifre[4],i=0,j=7,kp=0;
const char pass[4]={'1','2','3','4'}; // þifre 1234 olarak belirlendi.
char  keypadPort at PORTD; // tuþtakýmý PORTC'ye baðlanacak.

void main() {
trisb.f7=0;
portb.f7=0;

Keypad_Init();                           // Keypadi kur.
Lcd_Init();                              // LCD'yi kur.
Lcd_Cmd(_LCD_CLEAR);                     // LCD'yi temizle
Lcd_Cmd(_LCD_CURSOR_OFF);                // Ýmleci kapat.
Lcd_out(1,1,"Sifreyi Giriniz:");
lcd_out(2,7,"____");
while(1)
{
kp=0;
while(kp==0)// Herhangi bir tuþa basýlmazken sürekli tuþlarý tarayan altprogram.
{
kp=Keypad_Key_Click();//tuþtakýmna basýlýnca deðeri al.
delay_ms(10);// 10ms'lik gecikme þart.
}

switch (kp) {// ASCII dönüþümü yapýlýyor.(Mesela 1 karakterine denk gelen ASCII kod 49'dur.)
case  1: kp = 49; break; // 1
case  2: kp = 50; break; // 2
case  3: kp = 51; break; // 3
//case  4: kp = 65; break; // A //4x4 keypad kullanýldýðýnda bu kýsýmlar da koda dahil edilebilir.
case  5: kp = 52; break; // 4
case  6: kp = 53; break; // 5
case  7: kp = 54; break; // 6
//case  8: kp = 66; break; // B
case  9: kp = 55; break; // 7
case 10: kp = 56; break; // 8
case 11: kp = 57; break; // 9
//case 12: kp = 67; break; // C
case 13: kp = 42; break; // *
case 14: kp = 48; break; // 0
case 15: kp = 35; break; // #
//case 16: kp = 68; break; // D
}
lcd_chr(2,j,kp);
j++;
if(j==11)j=7;
sifre[i]=kp;
i++;
if(i==4)
{
i=0;
if(sifre[0]==pass[0] && sifre[1]==pass[1] && sifre[2]==pass[2] && sifre[3]==pass[3]) // Þifre doðruysa 10 saniye boyunca röleyi çektir...
{
portb.f7=1;
lcd_cmd(1),
lcd_out(1,1,"Sifre Dogru!");
delay_ms(500);
Lcd_out(1,1,"Sifreyi Giriniz:");
lcd_out(2,7,"____");
portb.f7=0;
}
else               // Þire yanlýþsa tekrar þifre girilmesini iste...
{
Lcd_Cmd(1);
Lcd_Out(1,1,"Sifre Yanlis!");
portb.f7=0;
delay_ms(500);
Lcd_out(1,1,"Sifreyi Giriniz:");
lcd_out(2,7,"____");
}
}
}
}
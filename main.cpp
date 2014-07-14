#include "mbed.h"
//アナログ入力3ch
AnalogIn VOL(dp9); //10k ohm ボリューム
AnalogIn TH(dp10); //THC サーミスター
AnalogIn IC(dp11); //フォトIC

//デジタル入力トグルスイッチ
DigitalIn SWL(dp26,PullUp); //トグルスイッチ 左側
DigitalIn SWR(dp25,PullUp); //トグルスイッチ 右側

//デジタル入力タクトスイッチ
DigitalIn TSG(dp17,PullUp); //タクトスイッチ緑
DigitalIn TSR(dp6,PullUp);  //タクトスイッチ赤

//基板LED,赤・緑
DigitalOut DLEDG(dp14,0);  //基板LED緑
DigitalOut DLEDR(dp28,0);  //基板LED赤

//dp1,dp2接続LED（付属のLEDを接続する）
PwmOut LEDR(dp1);  //Pwm LED 赤色 
PwmOut LEDG(dp2);  //Pwm LED 緑色

//PC接続、シリアルターミナル
Serial pc(USBTX, USBRX); // tx, rx

float VOLLED,THLED,ICLED;

int main() {
pc.baud(115200);//シリアル通信設定
while(1) {
//VOL連動赤色LED
LEDR = 0.7 + ( VOL.read() * 0.3);
VOLLED = LEDR;
                printf("\033[1;1H");
                printf("VOL.In %.6f\n", VOL.read());
                printf("\033[1;20H");
                printf("VOL-PWM-OUT %.6f\n", VOLLED);
//トグルスイッチ左、サーミスター（THC）連動緑色LED
if(SWL && !SWR) {
                LEDG = 1.0 - ((TH.read()*0.85));
                THLED = LEDG;
                printf("\033[2;1H");
                printf("THU.In %.6f\n", TH.read());
                printf("\033[2;20H");
                printf("THLED-PWM-OUT %.6f\n", THLED);


        }
//トグルスイッチ右、フォトIC（IC）連動緑色LED
                else if (SWR && !SWL){
                LEDG = 0.65 + (IC.read() * 1.25);
                ICLED = LEDG;
                printf("\033[3;1H");
                printf("IC.In %.6f\n", IC.read());
                printf("\033[3;20H");
                printf("ICLED-PWM-OUT %.6f\n", ICLED);

                             }

DLEDG = !TSG;//タクトスイッチ緑
DLEDR = !TSR;//タクトスイッチ赤
        }
}

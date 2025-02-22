float myArray[] = {65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 64, 64, 64, 65, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 64, 65, 65, 65, 65, 65, 65, 65, 64, 65, 64, 64, 65, 64, 64, 65, 64, 64, 64, 64, 65, 64, 64, 65, 65, 65, 65, 64, 65, 65, 65, 65, 64, 64, 65, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 64, 65, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 78, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79, 78, 78, 78, 78, 78, 78, 78, 78, 78, 77, 77, 77, 77, 78, 78, 79, 79, 79, 79, 79, 79, 78, 78, 78, 78, 78, 78, 78, 77, 77, 77, 77, 77, 77, 77, 77, 77, 76, 76, 76, 76, 76, 75, 76, 75, 75, 75, 75, 75, 75, 75, 75, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74,};
float kernel[] = {0.05, 0.24, 0.4, 0.24, 0.05};
float G[] = {65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 64, 64, 64, 65, 64, 64, 64, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 65, 64, 65, 65, 65, 65, 65, 65, 65, 64, 65, 64, 64, 65, 64, 64, 65, 64, 64, 64, 64, 65, 64, 64, 65, 65, 65, 65, 64, 65, 65, 65, 65, 64, 64, 65, 64, 64, 64, 64, 64, 64, 64, 64, 64, 65, 64, 65, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 78, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 79, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 78, 79, 78, 78, 78, 78, 78, 78, 78, 78, 78, 77, 77, 77, 77, 78, 78, 79, 79, 79, 79, 79, 79, 78, 78, 78, 78, 78, 78, 78, 77, 77, 77, 77, 77, 77, 77, 77, 77, 76, 76, 76, 76, 76, 75, 76, 75, 75, 75, 75, 75, 75, 75, 75, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74, 74,};
int N = 200, Nk = 5;
float den = 0, c = 0, zj = 0;
void setup()
{
  Serial.begin(9600);
}

void loop()
{
  den = 0;
  for (int i = 0; i < Nk; i++) {
    den = den + kernel[i];
  }

  for (int i = 0; i < N - Nk; i++) {
    for (int i2 = 0; i2 < Nk; i2++) {
      c = c + kernel[i2] * myArray[i2 + i];
    }
    c = c / den;
    Serial.print(c);
    Serial.print(",");
    Serial.println(myArray[i + 2] + 70);
    c = 0;
  }

  SNR();
}

void SNR() {

  //Promedio señal original v1
  float sum = 0;
  for (int i = 0; i < 90; i++) {
    sum = sum + G[i];
  }
  float promedio = sum / 90;
  float v1 = ((promedio * 5) / 1023);
  Serial.println(String("Valor voltaje señal: ") + String(v1));
  Serial.print(",");

  //Promedio señal Suavizada (v2) metodo de Gauss
  float sum2 = 0;
  for (int i = 0; i < 90; i++) {
    sum2 = sum2 + G[i + 2];
  }
  float promedio2 = sum2 / 90;
  float v2 = ((promedio2 * 5) / 1023);
  Serial.println(String("Valor voltaje del filtro: ") + String(v2));
  Serial.print(",");

  //Metrica SNR m=20*log(v2/v1)
  float metrica = 20 * log(v2 / v1);
  Serial.println(String("Valor metrica snr en dbs:") + String(metrica));
  Serial.print(",");

}

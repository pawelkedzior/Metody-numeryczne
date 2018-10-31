#include <iostream>
#include <fstream>

using namespace std;

int main (void)
{
    int i=0;
    int j=0;
    float macierz[128][128];
    float x[128];
    float a[128];
    fstream plik;
    plik.open("Zad2.txt",ios::out);
    for (i=0;i<128;i++) //tworzenie wektora wyników z
        a[i]=1;
    for (i=0;i<128;i++) //tworzenie macierzy A
        {
           for (j=0;j<128;j++)
               {
                if (j==i)
                   macierz[j][i]=4;
                else
                    if (i==j-1||i==j+1||i==j-4||i==j+4)
                       macierz[j][i]=1;
                    else
                        macierz[j][i]=0;
               }
        }
    for (i=0;i<128;i++)//Tworzenie wektora x
        x[i]=1;
        
//Metoda Gaussa-Seidela        
        
    for (int h=0;h<30;h++)//Wykonywanie trzydziestu przybli¿eñ - metoda Gaussa-Seidela
    {
    for (i=0;i<128;i++)
        {
              float  f=0;
              for (j=0;j<128;j++)
                  {
                   if ((j==i-4)||(j==i-1)||(j==i+1)||(j==i+4))
                      f=f+x[j]*macierz[i][j];
                  }
              x[i]=(a[i]-f)/macierz[i][i];
        }
    }  
    plik<<"Metoda Gaussa-Seidela"<<endl; //Wypisywanie obliczonego przybli¿enia wektora x
    plik<<"Warunki pocz¹tkowe:\nWektor x sk³ada siê z samych jedynek, ";
    plik<<"wektor wynikowy równie¿."<<endl<<endl;
    plik<<"Wyniki 30-stu przybli¿eñ:"<<endl;
    for (i=0;i<128;i++)  
        plik<<"x"<<i+1<<"="<<x[i]<<endl;
        
//Metoda Jakobiego        
        
    for (i=0;i<128;i++) //Tworzenie nowego wektora x
        x[i]=1;
    {
        float x2[128];
        for (i=0;i<128;i++) //Tworzenie kopii wektora x
            x2[i]=1;  
        for (int h=0;h<5000;h++)//Wykonywanie piêciu tysiêcy przybli¿eñ - metoda Jakobiego
            {
                 for (i=0;i<128;i++)
                 {
                     float  f=0;
                     for (j=0;j<128;j++)
                     {
                          if ((j==i-4)||(j==i-1)||(j==i+1)||(j==i+4))
                             f=f+x2[j]*macierz[i][j];
                     }
                     x[i]=(a[i]-f)/macierz[i][i];
                 }
                 for (i=0;i<128;i++)
                     x2[i]=x[i];
            }  
    }
    plik<<endl<<endl<<"Metoda Jakobiego"<<endl; //Wypisywanie obliczonego przybli¿enia wektora x
    plik<<"Warunki pocz¹tkowe:\nWektor x sk³ada siê z samych jedynek, ";
    plik<<"wektor wynikowy równie¿."<<endl<<endl;
    plik<<"Wyniki piêciu tysiêcy przybli¿eñ:"<<endl;
    for (i=0;i<128;i++)  
        plik<<"x"<<i+1<<"="<<x[i]<<endl;
        
//Metoda sprzê¿onych gradientów        
        
    {
        for (i=0;i<128;i++) //Tworzenie nowego wektora x
            x[i]=1;
        float pk[128];
        float p[128];
        float rk[128];
        float r[128];
        float alfa;
        float beta;
        for (i=0;i<128;i++)//Obliczanie pierwszych p i r
            {
             float f=0;
             for (j=0;j<128;j++)
                 {
                  if ((j==i-4)||(j==i-1)||(j==i+1)||(j==i+4)||(j==i))              
                     f=f+macierz[i][j]*x[j];
                 }
             r[i]=a[i]-f;
             p[i]=r[i];
            }
        for (int h=0;h<18;h++)//Wykonywanie powtórzeñ
           {
            {//Obliczanie wspó³czynnika alfa
            float f=0;
            float e=0;
            for (i=0;i<128;i++)
                {
                 f+=r[i]*r[i];
                 pk[i]=0;
                 for (j=0;j<128;j++)
                     {
                          if ((j==i-4)||(j==i-1)||(j==i+1)||(j==i+4)||(j==i))
                             pk[i]+=macierz[i][j]*p[j];
                     }
                 e+=p[i]*pk[i];
                }
            alfa=f/e;
            }
            for (i=0;i<128;i++)//obliczanie k+1-szego r
                rk[i]=r[i]-pk[i]*alfa;
            {//obliczanie wspó³æzynnika beta    
             float f=0;
             float e=0;
             for (j=0;j<128;j++)
                 {
                     f+=rk[j]*rk[j];
                     e+=r[j]*r[j];
                 }
             beta=f/e;
            }
            for (i=0;i<128;i++)//Obliczanie k+1-szego wspó³czynnika p oraz k+1-szego przybli¿enia.
                {
                 x[i]+=alfa*p[i];
                 p[i]=rk[i]+beta*p[i];
                 r[i]=rk[i];
                }
           }
           plik<<endl<<endl<<"Metoda sprzê¿onych gradientów"<<endl; //Wypisywanie obliczonego przybli¿enia wektora x
           plik<<"Warunki pocz¹tkowe:\nWektor x sk³ada siê z samych jedynek, ";
           plik<<"wektor wynikowy równie¿."<<endl<<endl;
           plik<<"Wyniki osiemnastu przybli¿eñ:"<<endl;
           for (i=0;i<128;i++)  
               plik<<"x"<<i+1<<"="<<x[i]<<endl;
    }    
    plik.close();
    return 0;
}

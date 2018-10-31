#include <iostream>
#include <fstream>

using namespace std;

int main (void)
{
    int i=0;
    int j=0;
    double macierz[7][7];
    double x[7];
    double a[7];
    fstream plik;
    plik.open("Zad1.txt",ios::out);
    for (i=0;i<7;i++) //tworzenie wektora wyników z
        a[i]=i+1;
    for (i=0;i<7;i++) //tworzenie macierzy A
        {
           for (j=0;j<7;j++)
               {
                if (j==i)
                   macierz[j][i]=4;
                else
                    if (i==j-1||i==j+1)
                       macierz[j][i]=1;
                    else
                        macierz[j][i]=0;
               }
        }
    for (i=0;i<7;i++) //Wypisywanie równania
        {
         if ((i!=0)&&(i!=6)&&(i!=3))
            {
            plik<<"      |";
            for (j=0;j<7;j++)
                plik<<macierz[j][i];
            plik<<"| |x"<<i+1<<"| |z"<<i+1<<"="<<a[i]<<"|"<<endl;
            }
         else
             if ((i!=3)&&(i!=6))
                {
                plik<<"      /";
                for (j=0;j<7;j++)
                    plik<<macierz[j][i];
                plik<<"\\ /x"<<i+1<<"\\ /z"<<i+1<<"="<<a[i]<<"\\"<<endl;
                }
             else
                 if (i!=3)
                    {
                    plik<<"      \\";
                    for (j=0;j<7;j++)
                        plik<<macierz[j][i];
                    plik<<"/ \\x"<<i+1<<"/ \\z"<<i+1<<"="<<a[i]<<"/"<<endl;
                    }
                 else
                     {
                     plik<<"A*x=z=|";
                     for (j=0;j<7;j++)
                         plik<<macierz[j][i];
                     plik<<"|*|x"<<i+1<<"|=|z"<<i+1<<"="<<a[i]<<"|"<<endl;
                     }
        }
    for (j=1;j<7;j++) //Przekszta³canie macierzy w macierz trójk¹tn¹
        {
            for (i=0;i<7;i++)
                {
                    macierz[j][i]=macierz[j][i]-macierz[j-1][i]/macierz[j-1][j-1];
                }
                a[j]=a[j]-a[j-1]/macierz[j-1][j-1];
        }
    plik<<endl;    
    for (i=6;i>-1;i--)  //Obliczanie wektora x po przekszta³ceniu macierzy A w macierz trójk¹tn¹
        {
           if (i==6)  
              x[i]=a[i]/macierz[i][i];
           else
               x[i]=(a[i]-x[i+1])/macierz[i][i];
        }
    plik<<"Macierz trójk¹tna po przekszta³ceniu"<<endl;
    for (i=0;i<7;i++) //Wypisywanie macierzy trójk¹tnej 
        {
        for (j=0;j<7;j++)
            plik<<macierz[i][j]<<" ";
        plik<<endl;
        }
    plik<<endl<<"Wektor z po przekszta³ceniu macierzy A"<<endl;
    for (i=0;i<7;i++) //Wypisywanie wektora z po przekszta³ceniu macierzy A w macierz trójk¹tn¹
        {
         plik<<"z"<<i+1<<"="<<a[i];
         plik<<endl;
        }
    plik<<endl<<"Wektor x"<<endl;
    for (i=0;i<7;i++)  //Wypisywanie obliczonego wektora x
        plik<<"x"<<i+1<<"="<<x[i]<<endl;
    plik.close();
    return 0;
}

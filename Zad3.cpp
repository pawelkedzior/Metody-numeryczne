#include <iostream>
#include <fstream>

using namespace std;

int main (void)
{
    int i=0;
    int j=0;
    float macierz[63][63];
    float x[65];
    float a[65];
    float fbis[65];
    fbis[0]=0;
    fbis[64]=0;
    float h;
    fstream plik;
    plik.open("Zad3.txt",ios::out);
    for (i=0;i<65;i++) //obliczanie wêz³ów
        x[i]=-1+static_cast<float>(i)/32;
    for (i=0;i<65;i++) //obliczanie wartoœci funkcji w wêz³ach
        a[i]=1/(1+5*x[i]*x[i]);
    plik<<"Obliczone wartoœci funkcji:"<<endl<<endl;
    for (j=0;j<65;j++)
        plik<<"x"<<j+1<<"="<<x[j]<<"               f(x"<<j+1<<")="<<a[j]<<endl;
    h=x[1]-x[0];
    h=6/(h*h);
    for (i=0;i<63;i++) //tworzenie macierzy A
        {
           for (j=0;j<63;j++)
               {
                if (j==i)
                   macierz[i][j]=4;
                else
                    if (i==j-1||i==j+1)
                       macierz[i][j]=1;
                    else
                        macierz[i][j]=0;
               }
        }
    {
    float prawy[63];
    for (i=0;i<63;i++)
        {
             prawy[i]=(a[i]-2*a[i+1]+a[i+2])*h;
        }
    for (j=0;j<63;j++) //Obliczanie wartoœci drugiej pochodnej funkcji
        {
            for (i=0;i<63;i++)
                {
                    macierz[j][i]=macierz[j][i]-macierz[j-1][i]/macierz[j-1][j-1];
                }
                prawy[j]=prawy[j]-prawy[j-1]/macierz[j-1][j-1];
        }   
    for (i=62;i>-1;i--)
        {
           if (i==62)  
              fbis[i+1]=prawy[i]/macierz[i][i];
           else
              fbis[i+1]=(prawy[i]-fbis[i+2])/macierz[i][i];
        } 
    }  
    h=x[1]-x[0];
    plik<<endl<<endl<<"Obliczone wartoœci drugich pochodnych:"<<endl<<endl;
    for (j=0;j<65;j++)
        plik<<"f''"<<j+1<<"="<<fbis[j]<<endl;
    plik<<endl<<endl;
    float wielomiany[64][4];//Obliczanie wspó³czynników dla danego wielomianu
    for (i=0;i<64;i++)
        {
             wielomiany[i][0]=(1/(6*h))*(fbis[i+1]-fbis[i]);
             wielomiany[i][1]=(1/(2*h))*(fbis[i]*x[i+1]-fbis[i+1]*x[i]);
             wielomiany[i][2]=(1/h)*(a[i+1]-a[i])+(h/6-x[i+1]*x[i+1]/(2*h))*fbis[i]+(x[i]*x[i]/(2*h)-h/6)*fbis[i+1];
             wielomiany[i][3]=(1/h)*(a[i]*x[i+1]-a[i+1]*x[i])+fbis[i]*(x[i+1]*x[i+1]*x[i+1]/(6*h)-h*x[i+1]/6)+fbis[i+1]*(h*x[i]/6-x[i]*x[i]*x[i]/(6*h));
        }
    plik<<endl<<"Przybli¿one funkcje w kolejnych przedzia³ach:"<<endl<<endl;
        for (i=0;i<64;i++)
            {
                 plik<<"y"<<i+1<<"(x)="<<wielomiany[i][0]<<"*x^3";
                 if (wielomiany[i][1]>0)
                    plik<<"+";
                 plik<<wielomiany[i][1]<<"*x^2";
                 if (wielomiany[i][2]>0)
                    plik<<"+";
                 plik<<wielomiany[i][2]<<"*x";
                 if (wielomiany[i][3]>0)
                    plik<<"+";
                 plik<<wielomiany[i][3]<<endl/*<<endl*/;
            }
    plik<<endl<<"Obliczanie wartoœci przybli¿onych wielomianów(wraz z ich wypisaniem)";
    plik<<" dla wartoœci rosn¹cych co 1/320 w przedziale [-1;1].";
    plik<<" Przedzia³y zmieniaj¹ siê co 1/32."<<endl<<endl;
    for (i=0;i<641;i++)//Wypisywanie przybli¿onych wielomianów i wartoœci funkcji dla x-ów
                       //rosn¹cych co 1/320              
        {
             float d;
             d=-1+static_cast<float>(i)/320;
             if (i!=640)
                {
                 plik<<"y"<<(i/10)+1<<"(x"<<i+1<<")=";
                 plik<<wielomiany[i/10][0]*d*d*d+wielomiany[i/10][1]*d*d+wielomiany[i/10][2]*d+wielomiany[i/10][3]<<endl;
                }
             else
                 {
                 plik<<"y"<<((i-1)/10)+1<<"(x"<<i+1<<")=";
                 plik<<wielomiany[63][0]*d*d*d+wielomiany[63][1]*d*d+wielomiany[63][2]*d+wielomiany[63][3]<<endl;
                 }
        }
    plik.close();
    return 0;
}

#include "CMaterialInterpolacao.h"

CMaterialInterpolacao::CMaterialInterpolacao(std::string fileName){
    std::string strTemporaria;
    int r, g, b, alpha;

    QDir dir; std::string path = dir.absolutePath().toStdString();
    std::ifstream file(path+"/materiais//"+fileName);
    if (file.is_open()){
        std::getline(file, strTemporaria);
        std::getline(file, name);

        file >> r; file >> g; file >> b; file >> alpha;
        color = QColor(r, g, b, alpha);

        file >> rho; file >> cp;

        double x1, x2, y1, y2;
        file >> x1 >> y1;
        xmin = x1;
        while(file >> x2 >> y2){
            retaInterpolacao.push_back( CSegmentoReta(x1,y1,x2,y2) );
            x1 = x2;
            y1 = y2;
        }
        xmax = x1;
        edx = (xmax-xmin)/ (retaInterpolacao.size()-1);
    }
    else{
        std::cout<<"can't open file!" << std::endl;
    }
}

double CMaterialInterpolacao::getThermalConst(double T){
    return rho*cp/getK(T);
}

double CMaterialInterpolacao::getK(double T){
    if( T <= xmin )
      return retaInterpolacao[0].Fx(T);
    else if(T >= xmax)
      return retaInterpolacao[retaInterpolacao.size()-1].Fx(T);
    // chute inicial, et = Estimativa do Trecho de reta que atende valor de x.
    int et = (T - xmin) / edx;
    while(true){  // procura pelo trecho de reta que contempla x.
      if( T < retaInterpolacao[et].Xmin() and et > 1 )
        et--;
      else if ( T > retaInterpolacao[et].Xmax() and et < retaInterpolacao.size()-1 )
        et++;
      else
        break;
    };
    return retaInterpolacao[et].Fx( T );   // calculo de Fx(x).
  }

#include<iostream>
#include<vector>
#include<algorithm>
#include<cfloat>
#include<sstream>
#include<string>
#include<fstream>

using namespace std;

class trier				// Fonction de tri en ordre décroissant des objets à empaqueter étant donné que nous utilisont un miniheap
{
public:
	bool operator()(float i, float j)
	{
		return (i > j);
	}

};
class Bin
{
public:
	Bin(){
		this->tailleTotale = 1.0;
		this->tailleRestante = 1.0;
		this->tailleUtilise = 0.0;
	}
	float tailleTotale;
	float tailleRestante;
	float tailleUtilise;
	vector<float>contenuBin;	//Vecteur des objets dans le bin
};
class BinPacking
{
public:
	void ajouter(float valeur);
	void afficher();
	void afficherBins();
	void FFD();
	void BFD();
private:
	int a;
	vector <float> valeurs;
	vector<Bin *> Bins;

};

void BinPacking::afficherBins()
{
	cout << "Affichage du contenu des bins :"<<endl;
	for (int i = 0; i < Bins.size(); i++)
	{
		cout << "Contenu du Bin " << i << " :" ;
		for (int j = 0; j < Bins[i]->contenuBin.size(); j++)
		{
			cout << Bins[i]->contenuBin[j] << "\t";
		}
		cout << endl;
	}

}
void BinPacking::FFD()
{
	Bin *bin = new Bin();
	Bins.push_back(bin);

	for (int i = 0; i < valeurs.size(); i++)
	{
		float temp = valeurs[i];
		bool present = false;
		for (int j = 0; j < Bins.size(); j++)
		{
			if (Bins[j]->tailleUtilise + temp < 1)
			{
				Bins[j]->tailleRestante -= temp;
				Bins[j]->tailleUtilise += temp;
				Bins[j]->contenuBin.push_back(temp);
					
					present = true;
					break;
			}
		}
		if (present == false)
		{
	
			Bin *bin = new Bin();
			bin->contenuBin.push_back(temp);
			bin->tailleRestante -= temp;
			bin->tailleUtilise += temp;
			Bins.push_back(bin);
		}
	}
}

void BinPacking::BFD()
{
	Bin *bin = new Bin();
	Bins.push_back(bin);

	for (int i = 0; i < valeurs.size(); i++)
	{
		float temp = valeurs[i];
		bool present = false;
		int plus_petit = INT_MAX;
		int numeroBin = 0;
		for (int j = 0; j < Bins.size(); j++)
		{
			if (Bins[j]->tailleUtilise + temp < 1)
			{
				plus_petit = Bins[j]->tailleRestante;//on stocke le plus petit espace;
				numeroBin = j;//on retient le bin qui avait le plus petit espace restant
				present = true;
			}

		}
		if (present)//il ya une place dans un Bin
		{
			Bins[numeroBin]->tailleRestante -= temp;
			Bins[numeroBin]->tailleUtilise += temp;
			Bins[numeroBin]->contenuBin.push_back(temp);
			
		}
		else //il n'ya plus de place, on va creer un nouveau Bin
		{
			
			Bin *bin = new Bin();
			bin->contenuBin.push_back(temp);
			bin->tailleRestante -= temp;
			bin->tailleUtilise += temp;
			Bins.push_back(bin);
		}
	}

}
void BinPacking::afficher()
{
	sort(valeurs.begin(), valeurs.end(), trier());
	cout << "Les valeures contenues sont: " << endl;
	for (vector<float>::iterator it = valeurs.begin(); it != valeurs.end(); it++)
	{
		cout << *it << " - ";
	}
	cout << endl << endl;
}
void BinPacking::ajouter(float valeur)
{
	valeurs.push_back(valeur);
}

int main()
{
	BinPacking Bin;
	string fichier("BinPacking.txt");
	ifstream Fichier(fichier.c_str());
	int i = 0;

	if (Fichier.good())
	while (Fichier.good())
	{
		i++;
		int y = 0;
		string ligne;

		getline(Fichier, ligne);
		stringstream ss(ligne);
		while (!ss.eof())
		{
			string mot;
			ss >> mot;
			float valeur = (float)atof(mot.c_str());
	
			y++;
			Bin.ajouter(valeur);
		}
		
	}
	int choix;

	Bin.afficher();
	cout << "Voulez vous faire le first fit ou le best fit ? \n1 pour first et 2 pour le best fit " << endl;
	cin >> choix;

	if (choix == 1)
		Bin.FFD();
	else if (choix == 2)
		Bin.BFD();

	Bin.afficherBins();
	return 0;
}
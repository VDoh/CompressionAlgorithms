#include <iostream>
#include <vector>
#include <string>


using namespace std;

/*Funkcja kompresji ByteRun
@param chain -> rozpatrywany ciag znakow
@param length -> dlugosc ciagu znakow
return -> zakodowany vektor
*/
vector <string> ByteRunEncoding(const string chain, int length)
{
	int i = 0;
	string numberFlag;
	vector<string> EncodedMessage;

	while (i < length)
	{
		if (chain[i] == chain[i + 1])
		{
			int j = 0;

			while ((chain[i + j] == chain[i + j + 1]) && (j < 127))
			{
				j++;
			}
			numberFlag = chain[i];

			int temp = -j;

			auto s = to_string(temp);

			EncodedMessage.push_back(s);
			EncodedMessage.push_back(numberFlag);

			cout << "{" << -j << "," << numberFlag << "}" << endl;
			i += (j + 1);
		}

		else
		{
			int j = 0;

			while ((chain[i + j] != chain[i + j + 1]) && (j < 128))
			{
				j++;
			}

			int temp = j - 1;
			auto s = to_string(temp);
			EncodedMessage.push_back(s);

			cout << "{" << j - 1 << ",";

			string temp2;

			for (int p = 0; p < j; p++)
			{
				cout << chain[p + i] << ",";
				temp2 = chain[p + i];
				EncodedMessage.push_back(temp2);
			}
			cout << "}" << endl;

			i += j;
		}

	}
	return EncodedMessage;
}

/*Funkcja kompresji RLE
@param chain -> rozpatrywany ciag znakow
@param length -> dlugosc ciagu znakow
return -> zakodowany vektor
*/
vector<string> RLEEncoding(string chain, int length)
{
	int i = 0;
	string numberFlag;
	vector<string> EncodedMessage;

	while (i < length)
	{
		if (chain[i] == chain[i + 1])
		{
			int j = 1;

			while ((chain[i + j] == chain[i + j + 1]))
			{
				j++;
			}

			numberFlag = chain[i];
			auto s = to_string(j + 1);
			EncodedMessage.push_back(s);
			EncodedMessage.push_back(numberFlag);

			cout << "{" << j + 1 << "," << numberFlag << "}" << endl;
			i += (j + 1);
		}
		else
		{
			int j = 1;

			while ((chain[i + j] != chain[i + j + 1]))
			{
				j++;
			}

			auto s = to_string(j);
			EncodedMessage.push_back("0");
			EncodedMessage.push_back(s);
			string temp;

			cout << "{" << 0 << ", " << j << ", ";

			for (int p = 0; p < j; p++)
			{
				temp = chain[p + 1];
				cout << chain[p + i] << ",";
				EncodedMessage.push_back(temp);
			}

			cout << "}" << endl;
			i += j;
		}
	}

	return EncodedMessage;
}


/*Funkcja kompresji LZW
@param chain -> rozpatrywany ciag znakow
@param alphabet -> alfabet
return -> string
*/
string LZWEncoding(string chain, string alphabet)
{
	vector<string> dictionary;
	vector<string>::iterator it;
	string temp;

	for (int i = 0; i < alphabet.length(); i++)
	{
		temp = alphabet[i];
		dictionary.push_back(temp);
	}

	string finalResult = "";
	string result = "";
	string word = "";

	for (int i = 0; i < chain.length(); i++) {
		bool inDict = false;
		char bits = chain[i];
		string tempWord = word + bits;

		for (int d = 0; d < dictionary.size(); d++) {
			if (dictionary[d] == tempWord) {
				inDict = true;
				word = tempWord;
				break;
			}
		}

		if (!inDict) {
			it = find(dictionary.begin(), dictionary.end(), word);
			auto index = distance(dictionary.begin(), it);
			finalResult += to_string(index);
			result += word;
			cout << index << endl;

			dictionary.push_back(tempWord);
			word = bits;
		}
	}

	if (word != "") {
		it = find(dictionary.begin(), dictionary.end(), word);
		auto index = distance(dictionary.begin(), it);
		cout << index << endl;
		finalResult += to_string(index);
		result += word;
	}

	return finalResult;
}

/*Funkcja wyswietla zawartosc vektora
@param arr-> rozpatrywany wektor
*/
void IterateVector(vector<string> &arr)
{
	cout << "{";
	for (auto i = arr.begin(); i != arr.end(); ++i)
	{
		cout << *i << ", ";
	}
	cout << "}";
	cout << endl;
}

/*Funkcja liczy procent jak bardzo skompresowalsmy dane
@param lengthOfOriginal-> dlugosc ciagu znakow podanego do kompresji
@param lengthOfEncoded-> dlugosc ciagu znakow zakodowanych
return -> procent */
float CountPercentage(int lengthOfOriginal, int lengthOfEncoded)
{
	float x = lengthOfEncoded * 100 / lengthOfOriginal;

	return x;
}

void Menu()
{
	cout << "1. ByteRun" << endl;
	cout << "2. RLE" << endl;
	cout << "3. LZW" << endl;
	cout << "4. ZAKONCZ" << endl;
}

void Question()
{
	cout << "1. Use standard 111222223333312333333" << endl;
	cout << "2. Input data from keybord" << endl;
}

/*Wyswietla poszczegolne znaki w stringu
@param txt -> rozpatrywany ciag znakow
*/
void ShowNumbers(string txt)
{
	int length = txt.length();

	cout << "{";

	for (int i = 0; i < length; i++)
	{
		cout << txt[i] << ", ";
	}

	cout << "}";
	cout << endl;
}

/*Menu*/
void PickCompression()
{
	int pick;
	int quest;
	bool flag = true;

	while (flag)
	{
		cin >> pick;

		switch (pick)
		{
		case 1:
		{
			string txt;
			Question();
			cin >> quest;

			if (quest == 1)
			{
				txt = "111222223333312333333";
			}
			else if (quest == 2)
			{
				cin >> txt;
			}

			int lengthOfTxt = txt.length();
			cout << "Dane do kompresji:" << endl;
			ShowNumbers(txt);
			vector <string> compresedData;

			cout << "Wyniki:" << endl;
			compresedData = ByteRunEncoding(txt, lengthOfTxt);

			cout << "Pelne rozwiazanie: " << endl;
			IterateVector(compresedData);

			float percentage = CountPercentage(lengthOfTxt, compresedData.size());

			cout << "Kompresja: " << lengthOfTxt << "->" << compresedData.size() << ", " << percentage << "%" << endl;
			break;
		}

		case 2:
		{
			string txt;
			Question();
			cin >> quest;

			if (quest == 1)
			{
				txt = "111222223333312333333";
			}
			else if (quest == 2)
			{
				cin >> txt;
			}

			int lengthOfTxt = txt.length();
			cout << "Dane do kompresji:" << endl;
			ShowNumbers(txt);
			vector <string> compresedData;

			cout << "Wyniki:" << endl;
			compresedData = RLEEncoding(txt, lengthOfTxt);

			cout << "Pelne rozwiazanie: " << endl;
			IterateVector(compresedData);

			float percentage = CountPercentage(lengthOfTxt, compresedData.size());

			cout << "Kompresja: " << lengthOfTxt << "->" << compresedData.size() << ", " << percentage << "%" << endl;
			break;
		}

		case 3:
		{
			string txt;
			string alphabet;
			Question();
			cin >> quest;

			if (quest == 1)
			{
				txt = "111222223333312333333";
				alphabet = "123";
			}
			else if (quest == 2)
			{
				cout << "Input alphabet: " << endl;
				cin >> alphabet;
				cout << "Input string" << endl;
				cin >> txt;
			}

			string encodedMessage;

			int lengthOfTxt = txt.length();
			cout << "Dane do kompresji: " << endl;
			ShowNumbers(txt);

			cout << "Wyniki:" << endl;
			encodedMessage = LZWEncoding(txt, alphabet);
			int lengthOfCompressed = encodedMessage.length();

			cout << "Pelne rozwiazanie: " << endl;
			cout << encodedMessage << endl;

			float percentage = CountPercentage(lengthOfTxt, lengthOfCompressed);

			cout << "Kompresja: " << lengthOfTxt << "->" << lengthOfCompressed << ", " << percentage << "%" << endl;
			break;
		}
		case 4:
		{
			flag = false;
			break;
		}

		}
	}
}


int main()
{
	Menu();
	PickCompression();

	return 0;
}
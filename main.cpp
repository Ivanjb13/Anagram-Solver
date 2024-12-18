
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in


// Functions for reading in dictionary
int loadWords(istream &dictfile, string dict[]);

int loadWords_aux(istream &dictfile, string dict[], int i);


// Functions for finding permutations
int recBlends(string word, const string dict[], int a, string results[]);

void RecFor(const string dict[], const int dictSize, string pre, string post,  int i, int size, string results[], int& nwords);

void recBlends_aux(const string dict[], const int dictSize, string pre, string post,  string results[], int& numResults);

// Functions for printing results
void showResults(const string results[], int);

void showResults_aux(const string results[], int, int);


int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;

    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }

    nwords = loadWords(dictfile, dict);

    cout << "Please enter a string for an anagram: ";
    cin >> word;

    int numMatches = recBlends(word, dict, nwords, results);
    if (!numMatches)
        cout << "No matches found" << endl;
    else
        showResults(results, numMatches);

    return 0;
}

int loadWords(istream &dictfile, string dict[]) {
  return loadWords_aux(dictfile, dict, 0);
}

int loadWords_aux(istream &dictfile, string dict[], int i) 
{
  if(i>=MAXDICTWORDS)
  {
    return i;
  }
  else 
  {
    if(dictfile>>dict[i])
    {
      return loadWords_aux(dictfile, dict,(i+1));
    }
  }
  return i;
}

void showResults(const string results[], int numMatches) 
{
    showResults_aux(results, numMatches,0);
}

void showResults_aux(const string results[], int numMatches, int i) {
  if(i>=MAXRESULTS||i>=numMatches)
  {
    return;
  }
  else 
  {
    cout<<results[i]<<endl;
    showResults_aux(results, numMatches,i+1);
  }
}


int recBlends(string word, const string dict[], int dictSize, string results[]) {
    int nwords=0;

    recBlends_aux(dict, dictSize, string(""), word, results, nwords);
    
    return nwords;
}

// Places the string s into results, returns the newly placed string's position
// Returns -1 if it's already in the array or if array is full
int insertloop (string results[], string s, int i) {
  if(i==MAXRESULTS)
  {
    return -1;
  }
  else if(results[i]=="")
  {
    results[i]=s;
    
    return i;
  }
  else if(results[i]==s)
  {
    return -1;
  }
  return insertloop(results, s,(i+1));

}

// returns true if word is in dict
bool isInDictionary(const string dict[], int size, string word, int i) {
  if(i>=size)
  {
    return false;
  }
  else if(dict[i]==word)
  {
    return true;
  }

  return isInDictionary(dict, size,word,(i+1));

}

void recBlends_aux(const string dict[], const int dictSize, string pre, string post,  string results[], int& nwords) {
  if (post == "")
   {       
        string perm = pre;
        if (!isInDictionary(dict, dictSize, perm, 0))
        {
          return;
        }
        
        int lastPos = insertloop(results, perm, 0); 
        if (lastPos == -1)
        {
            return;
        }
        nwords = lastPos+1;
        return;
    }
    int size=post.size();
    RecFor(dict, dictSize, pre, post, 0, size, results, nwords);

}

void RecFor(const string dict[], const int dictSize, string pre, string post, int i, int size, string results[], int& nwords) {
    if (i == size) 
    {
        return;
    }
    else 
    {
      recBlends_aux(dict, dictSize, (pre + post[i]), (post.substr(0,i) + post.substr(i+1)),  results, nwords);

      RecFor(dict, dictSize, pre, post, ++i, size, results, nwords);
    }
}

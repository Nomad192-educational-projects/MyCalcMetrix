#include "buisness_logic.h"
static bool openFile(string *nameFile, vector<string> *headers, vector<string> *republics, unsigned int *numberYears, vector<vector<string>> *dataVector);
static bool calc_metr(inMetrix *in, outMetrix *out, double *data, vector<vector<string>> *dataVector);
static vector <string> split(string s, string delimiter);

bool interfaceBundle(enum compilation comp, void *req, void *answer1, void *answer2, void *answer3,vector <vector<string>> *dataVector){
    bool result;
    switch (comp){
        case OPEN_FILE: result = openFile((string*)req, (vector<string>*) answer1, (vector<string>*) answer2, (unsigned int*) answer3, dataVector); break;
        case CALC_METR: result = calc_metr((inMetrix*)req, (outMetrix*)answer1, (double *)answer2, dataVector); break;
        case LOAD_DATA: result = true; break;}
    return result;
}


static bool openFile(string *nameFile, vector<string> *headers, vector<string> *republics, unsigned int *numberYears, vector<vector<string>> *dataVector){
    fstream dataFile(*nameFile, ios::in);
    bool result = false;
    if(dataFile.is_open()){
        result = true;
        string line;
        getline(dataFile, line);
        *headers = split(line, ",");
        getline(dataFile, line);
        vector <string> parts = split(line,",");
        dataVector->push_back(parts);
        int year = stoi(parts.at(0));
        (*numberYears) = 1;
        republics->push_back(parts.at(1));
        while(getline(dataFile, line)){ // первый год
            parts = split(line, ",");
            dataVector->push_back(parts);
            int currentYear = stoi(parts.at(0));
            if(currentYear!=year){
                (*numberYears)++;
                year = currentYear;
                break;
            }
            republics->push_back(parts.at(1));
        }
        while(getline(dataFile, line)){ // оставшиеся года
            parts = split(line, ",");
            dataVector->push_back(parts);
            int currentYear = stoi(parts.at(0));
            if(currentYear!=year){
                (*numberYears)++;
                year = currentYear;
            }
        }
        dataFile.close();
    }
    return result;
}

vector<string> split (string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

#include <QDebug>

static bool calc_metr(inMetrix *in, outMetrix *out, double *full_data, vector<vector<string>> *dataVector){
    double *data = new double[in->numberYears];
    size_t count = 0;
    for(unsigned int i = 0; i < in->numberYears; i++){
        //qDebug() << QString::fromStdString((*dataVector)[i * in->numberRepublics + in->republic][in->column]);
        if ((*dataVector)[i * in->numberRepublics + in->republic][in->column] != ""){
            data[count] = stod((*dataVector)[i * in->numberRepublics + in->republic][in->column]);
            full_data[i] = data[count];
            count++;
        }
        else
        {
            full_data[i] = 1.0/0.0;
        }
        qDebug() << data[count-1] << full_data[i] << isinf(full_data[i]);
    }
    for(unsigned int i = 0; i < count - 1; i++){
        for(unsigned int j = i + 1; j < count; j++){
            if(data[i] > data[j]){
                double buffer = data[i];
                data[i] = data[j];
                data[j] = buffer;
            }
        }
    }
    out->min = data[0];
    out->max = data[count - 1];
    if(!((count) % 2 == 0)){
        out->med = data[count / 2];
    }
    else{
        out->med = data[count / 2 - 1] + data[count / 2];
        out->med /= 2;
    }
    delete[] data;
    return true;
}



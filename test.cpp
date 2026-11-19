#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct PurchaseItem{
    string name;
    double price;
    int priority;
    double value;
    PurchaseItem(string n="",double p=0, int pr=0){
        name=n;
        price=p;
        priority=pr;
        value=calculateValue();
    }
    string getName(){
        return name;
    }
    double getPrice(){
        return price;
    }
    int getPriority(){
        return priority;
    }
    void setName(string n){
        name=n;
    }
    void setPrice(double p){
        price=p;
    }
    void setPriority(int pr){
        priority=pr;
    }
    void setValue(){
        value=calculateValue();
    }
    double calculateValue(){
        return priority/price;
    }
};

int login(const vector<string> &username, const vector<string> &password, string &un){
    bool flag=false;
    string name;
    cout<<"ENTER YOUR USERNAME: "<<endl;
    cin>>name;
    int i=0;
    int position;
    while(i<username.size() && flag==false){
        if(username[i]==name){
            flag=true;
            position=i;
        }else{
            i++;
        }
    }
    if(flag==false){
        return 0;
    }
    int tries=0;
    flag=false;
    string pwd;
    while(flag==false && tries<3){
        cout<<"ENTER YOUR PASSWORD: "<<endl;
        cin>>pwd;
        if(pwd==password[position]){
            flag=true;
        }else{
            cout<<"WRONG PASSWORD YOU HAVE " <<2-tries<< " TRIES LEFT"<<endl;
            tries++;
        }
    }
    if(flag==true){
        un=name;
        return 1;
    }else{
        return 0;
    }
}

int sign_up(vector<string> &username, vector<string> &password, vector<string> &nm, vector<string> &srnm, vector<double> &budg, string &un){
    string line;
    bool flag1;
    cout<<"CREATE YOUR USERNAME "<<endl;
    string uname;
    do{
        cin>>uname;
        bool flag2=false;
        int i=0;
        while(i<username.size() && flag2==false){
            if(username[i]==uname){
                flag2=true;
            }else{
                i++;
            }
        }
        flag1 = flag2;  
        if(flag1==true){
            cout<<"USERNAME ALREADY EXISTS. TRY AN OTHER ONE "<<endl;
        }
    }while(flag1==true);
    line.append(uname);
    line.append(",");
    cout<<"CREATE YOUR PASSWORD (MAKE SURE ITS STRONG AND YOU WRITE IT DOWN SOMEWHERE)"<<endl;
    string pwd;
    cin>>pwd;
    line.append(pwd);
    line.append(",");
    cout<<"ENTER YOUR NAME "<<endl;
    string n;
    cin>>n;
    line.append(n);
    line.append(",");
    cout<<"ENTER YOUR SURNAME "<<endl;
    string s;
    cin>>s;
    line.append(s);
    line.append(",");
    cout<<"ENTER YOUR BUDGET "<<endl;
    double a;
    cin>>a;
    line.append(to_string(a));
    ofstream f;
    f.open("account.txt",ios::app);
    if(!f.is_open()){
        cout<<"THE ACCOUNT WAS NOT CREATED BECAUSE OF A PROBLEM THAT OCCURRED WITH THE DATABASE. PLEASE TRY AGAIN LATER"<<endl;
        return 0;
    }
    f<<line<<endl;
    f.close();
    
    // Add new user to vectors
    username.push_back(uname);
    password.push_back(pwd);
    nm.push_back(n);
    srnm.push_back(s);
    budg.push_back(a);
    
    un=uname;
    return 1;
}

int file_is_empty(string file){
    ifstream f;
    f.open(file);
    string line;
    int i=0;
    while(getline(f,line) && i==0){
        i++;
    }
    f.close();
    if(i==0){
        return 1;
    }else{
        return 0;
    }
}

int position(const vector<string> &username, const string &un){
    for(int i=0; i<username.size(); i++){
        if(username[i]==un){
            return i;
        }
    }
    return -1;  // Return -1 if not found
}

int position2(const vector<PurchaseItem> &vobject,const string oname){
    for(int i=0; i<vobject.size(); i++){
        if(vobject[i].name==oname){
            return i;
        }
    }
    return -1;
}

void sort(vector<double> &vvalue, vector<PurchaseItem> &vobject){
    int n=vvalue.size();
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(vvalue[j]<vvalue[j+1]){
                double temp1=vvalue[j];
                vvalue[j]=vvalue[j+1];
                vvalue[j+1]=temp1;
                PurchaseItem temp2=vobject[j];
                vobject[j]=vobject[j+1];
                vobject[j+1]=temp2;
            }
        }
    }
}

void updateVvalues(vector<double> &vvalue, const vector<PurchaseItem> &vobject){
    vvalue.clear();
    for(int i=0; i<vobject.size(); i++){
        vvalue.push_back(vobject[i].value);
    }
}

int main(){
    string un;
    vector<string> username,password,nm,srnm;
    vector<double> budg;
    ifstream fin;
    fin.open("account.txt");
    string line;
    if(fin.is_open()){
        string tempname,temppwd,ten,tes;
        double tempb;
        while(getline(fin,line)){
            tempname=line.substr(0,line.find(","));
            line=line.substr(line.find(",")+1);
            temppwd=line.substr(0,line.find(","));
            line=line.substr(line.find(",")+1);
            ten=line.substr(0,line.find(","));
            line=line.substr(line.find(",")+1);
            tes=line.substr(0,line.find(","));
            line=line.substr(line.find(",")+1);
            tempb=stod(line);
            budg.push_back(tempb);
            username.push_back(tempname);
            password.push_back(temppwd);
            nm.push_back(ten);
            srnm.push_back(tes);
        }
    }else{
        cout<<"PROBLEM PROBLEM BETTER CALL THE MASTORA"<<endl;
        return 0;
    }
    fin.close();
    cout<<"\n";
    cout<<"ACTIONS: "<<endl;
    cout<<"1)LOGIN "<<endl;
    cout<<"2)SIGN-UP "<<endl;
    cout<<"3)EXIT "<<endl;
    cout<<"CHOOSE "<<endl;
    int choice;
    cin>>choice;
    if(choice==1){
        int x=login(username,password,un);
        if(x==1){
            cout<<"LOGGED IN SUCCESSFULLY"<<endl;
        }else{
            cout<<"LOGIN FAILED PLEASE TRY AGAIN LATER"<<endl;
            return 0;
        }
    }else if (choice==2){
        int x=sign_up(username,password,nm,srnm,budg,un);
        if(x==1){
            cout<<"YOU SIGNED UP SUCCESSFULLY FOR OUR APPLICATION"<<endl;
        }else{
            return 0;
        }
    }else{
        cout<<"END OF OPERATION"<<endl;
        return 0;
    }
    
    string file=un+".txt";
    int pos=position(username,un);
    if(pos==-1){
        cout<<"ERROR: USER NOT FOUND"<<endl;
        return 0;
    }
    
    vector<PurchaseItem> vobject;
    vector<double> vvalue;
    
    // Load user's wishlist
    ifstream userfile;
    userfile.open(file);
    if(userfile.is_open()){
        string fileline;
        while(getline(userfile,fileline)){
            PurchaseItem tempor;
            string tname;
            double tprice,tvalue;
            int tpriority;
            tname=fileline.substr(0,fileline.find(","));
            fileline=fileline.substr(fileline.find(",")+1);
            tprice=stod(fileline.substr(0,fileline.find(",")));
            fileline=fileline.substr(fileline.find(",")+1);
            tpriority=stoi(fileline.substr(0,fileline.find(",")));
            fileline=fileline.substr(fileline.find(",")+1);
            tvalue=stod(fileline);
            vvalue.push_back(tvalue);
            tempor.name=tname;
            tempor.price=tprice;
            tempor.priority=tpriority;
            tempor.value=tvalue;
            vobject.push_back(tempor);
        }
    }
    userfile.close();
    
    do{
        updateVvalues(vvalue, vobject);
        sort(vvalue,vobject);
        cout<<"\n";
        cout<<"ACTIONS: "<<endl;
        cout<<"1)VIEW WISHLIST "<<endl;
        cout<<"2)EDIT WISHLIST"<<endl;
        cout<<"3)EDIT BUDGET"<<endl;
        cout<<"4)EXIT"<<endl;
        cout<<"CHOOSE "<<endl;
        cin>>choice;
        switch(choice){
            case 1: {
               int x=file_is_empty(file);
               if(x==1){
                   cout<<"YOUR WISHLIST IS EMPTY "<<endl;
               }else{
                    cout<<"\n--- YOUR WISHLIST (SORTED BY VALUE) ---"<<endl;
                    for(int i=0; i<vobject.size(); i++){
                        cout<<"NAME: "<<vobject[i].name
                            <<" | PRICE: "<<vobject[i].price
                            <<" | PRIORITY: "<<vobject[i].priority
                            <<" | VALUE: "<<vobject[i].value<<endl;
                    }
                    cout<<"CURRENT BUDGET: "<<budg[pos]<<endl;
               }
               break;
            }
            case 2: {
               cout<<"\n";
               cout<<"ACTIONS: "<<endl;
               cout<<"1)DELETE ITEM "<<endl;
               cout<<"2)ADD ITEM "<<endl;
               cout<<"3)EDIT EXISTING ITEM "<<endl;
               cout<<"CHOOSE "<<endl;
               int option;
               cin>>option;
               if(option==1){
                  int x=file_is_empty(file);
                  if(x==1){
                     cout<<"YOUR WISHLIST IS EMPTY "<<endl;
                  }else{
                     cout<<"ENTER THE NAME OF THE ITEM YOU WANT TO DELETE: "<<endl;
                     string yname;
                     cin.ignore();
                     getline(cin, yname);
                     int pos2=position2(vobject,yname);
                     if(pos2==-1){
                        cout<<"THE ITEM WASN'T FOUND OR YOU DIDN'T ENTER THE CORRECT NAME "<<endl;
                     }else{
                        vobject.erase(vobject.begin()+pos2);
                        cout<<"ITEM DELETED SUCCESSFULLY"<<endl;
                     }
                  }
               }else if(option==2){
                  string tn;
                  double tp;
                  int tpr;
                  cout<<"ENTER THE NAME OF THE ITEM: "<<endl;
                  cin.ignore();
                  getline(cin, tn);
                  cout<<"ENTER THE PRICE OF THE ITEM: "<<endl;
                  cin>>tp;
                  cout<<"ENTER ITEM'S PRIORITY (1-10): "<<endl;
                  cin>>tpr;
                  PurchaseItem tempobj(tn,tp,tpr);
                  vobject.push_back(tempobj);
                  cout<<"ITEM ADDED SUCCESSFULLY"<<endl;
               }else if(option==3){
                   int x=file_is_empty(file);
                    if(x==1){
                        cout<<"YOUR WISHLIST IS EMPTY "<<endl;
                    }else{
                        cout<<"ENTER THE NAME OF THE ITEM YOU WANT TO EDIT: "<<endl;
                        string yname;
                        cin.ignore();
                        getline(cin, yname);
                        int pos2=position2(vobject,yname);
                        if(pos2==-1){
                            cout<<"THE ITEM WASN'T FOUND OR YOU DIDN'T ENTER THE CORRECT NAME "<<endl;
                        }else{
                            string tn;
                            double tp;
                            int tpr;
                            cout<<"ENTER THE NEW NAME OF THE ITEM: "<<endl;
                            getline(cin, tn);
                            cout<<"ENTER THE NEW PRICE OF THE ITEM: "<<endl;
                            cin>>tp;
                            cout<<"ENTER THE NEW PRIORITY OF THE ITEM: "<<endl;
                            cin>>tpr;
                            vobject[pos2].setName(tn);
                            vobject[pos2].setPrice(tp);
                            vobject[pos2].setPriority(tpr);
                            vobject[pos2].setValue();
                            cout<<"ITEM UPDATED SUCCESSFULLY"<<endl;
                        }
                    }
                }
                break;
            }
            case 3: {
                cout<<"\n";
                cout<<"CURRENT BUDGET: "<<budg[pos]<<endl;
                cout<<"ACTIONS: "<<endl;
                cout<<"1)ADD "<<endl;
                cout<<"2)SUBTRACT "<<endl;
                cout<<"CHOOSE: "<<endl;
                int t;
                cin>>t;
                if(t==1){
                    cout<<"HOW MUCH MONEY ARE YOU ADDING TO YOUR BALANCE? "<<endl;
                    double amount;
                    cin>>amount;
                    budg[pos]+=amount;
                    cout<<"NEW BUDGET: "<<budg[pos]<<endl;
                }else if(t==2){
                    cout<<"HOW MUCH MONEY ARE YOU SUBTRACTING FROM YOUR BALANCE? "<<endl;
                    double amount;
                    cin>>amount;
                    budg[pos]-=amount;
                    cout<<"NEW BUDGET: "<<budg[pos]<<endl;
                }
                break;
            }
            case 4: {
                cout<<"SAVING AND EXITING..."<<endl;
                break;
            }
            default: {
                cout<<"INVALID CHOICE"<<endl;
                break;
            }
        }
        ofstream userout;
        userout.open(file, ios::trunc);
        for(int i=0;i<vobject.size();i++){
            userout<<vobject[i].name<<","<<vobject[i].price<<","<<vobject[i].priority<<","<<vobject[i].value<<endl;
        }
        userout.close();
        ofstream accout;
        accout.open("account.txt", ios::trunc);
        for(int i=0;i<nm.size();i++){
            accout<<username[i]<<","<<password[i]<<","<<nm[i]<<","<<srnm[i]<<","<<budg[i]<<endl;
        }
        accout.close();
    }while(choice!=4);
    cout<<"END OF OPERATION :) "<<endl;
    return 0;
}
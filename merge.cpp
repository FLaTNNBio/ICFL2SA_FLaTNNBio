#include "merge.h"

int get_factor(vector<int>& icfl_list,int index){
    int max_factor=icfl_list.size()-1;

    for(int i=0;i<max_factor;i++){
        if(index >= icfl_list.at(i) && index < icfl_list.at(i+1)){
            return i;
        }
    }

    return max_factor;

}

std::vector<int> get_factor_list(vector<int>& icfl_list,int str_len){
    std::vector<int> res;
    res.reserve(str_len);
    for(int i=0;i<str_len;++i) res.push_back(get_factor(icfl_list,i));
    return res;
}


std::vector<bool> in_prefix_merge_bit_vector_5(const char* S, vector<int>& icfl_list, int icfl_list_size, vector<int> father, vector<int>& child,int father_lenght,std::vector<int>& is_custom_suffix){
    std::vector<bool> result;
    result.resize(father.size()+child.size());
    int temp_res;

    int i=0,j=0;

    //cout<<" last:"<<icfl_list[icfl_list.size()-1]<<" ";

    //cout<<"Comparing:\n";
    //printVec(father);
    //cout<<"\n";
    //printVec(child);
    //cout<<"\n";

    while( i<father.size() && j<child.size()){

        if(is_custom_suffix[father[i]] || is_custom_suffix[child[j]] ){
            //cout<<i<<" "<<j<<"\n";
            temp_res = strcmp(S+child[j],S+father[i]);
            if(temp_res<0){result.push_back(false);j++;}
            else{result.push_back(true);i++;}
        }

        else if(father[i] >= icfl_list[icfl_list_size-1] && child[j] >= icfl_list[icfl_list_size-1]){result.push_back(true);i++;}
        else if(get_factor(icfl_list,father[i])==get_factor(icfl_list,child[j])){result.push_back(false);j++;}
        else{
            if(father[i] >= icfl_list[icfl_list_size-1]){result.push_back(true);i++;}
            else if(child[j] >= icfl_list[icfl_list_size-1]){
                if(strcmp(S+child[j],S+father[i])<0){result.push_back(false);j++;}
                else{result.push_back(true);i++;}
            }
            else{
                if(father[i] > child[j]){result.emplace_back(false);j++;}
                else{
                    if(strcmp(S+child[j],S+father[i])<0){result.push_back(false);j++;}
                    else{result.push_back(true);i++;}
                }
            }
        }

    }

    while(j<child.size()){result.push_back(false);j++;}
    while(i<father.size()){result.push_back(true);i++;}

    return result;
}

//Migliorata la ricerca del fattore con vettore d'appoggio
std::vector<bool> in_prefix_merge_bit_vector_5_1(const char* S, vector<int>& icfl_list, int icfl_list_size, vector<int> father, vector<int>& child,int father_lenght,std::vector<int>& is_custom_suffix,vector<int>& factor_list){
    std::vector<bool> result;
    result.resize(father.size()+child.size());
    int i=0,j=0,temp_res;

    //cout<<"capacity: "<<result.capacity()<<"\n";
    //cout<<j<<"\n";
    //    cout<<i<<"\n";
    //    cout<<i+j<<"\n";

    while( i<father.size() && j<child.size()){
        //cout<<j<<"\n";
        //cout<<i<<"\n";
        //cout<<i+j<<"\n";
        if(is_custom_suffix[father[i]] || is_custom_suffix[child[j]] ){
            temp_res = strcmp(S+child[j],S+father[i]);
            if(temp_res<0){result.at(i+j)=false;j++;}
            else{result.at(i+j)=true;i++;}
        }

        else if(father[i] >= icfl_list[icfl_list_size-1] && child[j] >= icfl_list[icfl_list_size-1]){result.at(i+j)=true;i++;}
        else if(factor_list[father[i]]==factor_list[child[j]]){result.at(i+j)=false;j++;}
        else{
            if(father[i] >= icfl_list[icfl_list_size-1]){result.at(i+j)=true;i++;}
            else if(child[j] >= icfl_list[icfl_list_size-1]){
                if(strcmp(S+child[j],S+father[i])<0){result.at(i+j)=false;j++;}
                else{result.at(i+j)=true;i++;}
            }
            else{
                if(father[i] > child[j]){result.at(i+j)=false;j++;}
                else{
                    if(strcmp(S+child[j],S+father[i])<0){result.at(i+j)=false;j++;}
                    else{result.at(i+j)=true;i++;}
                }
            }
        }

    }
    //cout<<"a\n";
    while(j<child.size()){result.at(i+j)=false;j++;}
    //cout<<"a\n";
    while(i<father.size()){result.at(i+j)=true;i++;}

    return result;
}

//Restituisce direttamente la catena
std::vector<int> in_prefix_merge_bit_vector_5_2(const char* S, vector<int>& icfl_list, int icfl_list_size, vector<int>& father, vector<int>& child,int father_lenght,std::vector<int>& is_custom_suffix,vector<int>& factor_list){
    std::vector<int> result;
    result.resize(father.size()+child.size());
    int i=0,j=0,temp_res;

    while( i<father.size() && j<child.size()){
        if(is_custom_suffix[father[i]] || is_custom_suffix[child[j]] ){
            temp_res = strcmp(S+child[j],S+father[i]);
            if(temp_res<0){result.at(i+j)=child[j];++j;}
            else{result.at(i+j)=father[i];++i;}
        }

        else if(father[i] >= icfl_list[icfl_list_size-1] && child[j] >= icfl_list[icfl_list_size-1]){result.at(i+j)=father[i];++i;}
        else if(factor_list[father[i]]==factor_list[child[j]]){result.at(i+j)=child[j];++j;}
        else{
            if(father[i] >= icfl_list[icfl_list_size-1]){result.at(i+j)=father[i];++i;}
            else if(child[j] >= icfl_list[icfl_list_size-1]){
                if(strcmp(S+child[j],S+father[i])<0){result.at(i+j)=child[j];++j;}
                else{result.at(i+j)=father[i];++i;}
            }
            else{
                if(father[i] > child[j]){result.at(i+j)=child[j];++j;}
                else{
                    if(strcmp(S+child[j],S+father[i])<0){result.at(i+j)=child[j];++j;}
                    else{result.at(i+j)=father[i];++i;}
                }
            }
        }

    }
    while(j<child.size()){result.at(i+j)=child[j];++j;}
    while(i<father.size()){result.at(i+j)=father[i];++i;}

    return result;
}

std::vector<int> in_prefix_merge_bit_vector_6(const char* S, vector<int> icfl_list, int icfl_list_size, vector<int> father, vector<int> child){
    std::vector<int> result;
    result.reserve(father.size()+child.size());

    int i=0,j=0;

    //cout<<" last:"<<icfl_list[icfl_list.size()-1]<<" ";

    while( i<father.size() && j<child.size()){
        if(father[i] >= icfl_list[icfl_list_size-1] && child[j] >= icfl_list[icfl_list_size-1]){
            result.emplace_back(father[i]);
            i++;
        }
        else if(get_factor(icfl_list,father[i])==get_factor(icfl_list,child[j])){
            result.emplace_back(child[j]);
            j++;
        }
        else{
            if(father[i] >= icfl_list[icfl_list_size-1]){
                result.emplace_back(father[i]);
                i++;
            }
            else if(child[j] >= icfl_list[icfl_list_size-1]){
                if(strcmp(S+child[j],S+father[i])<0){
                    result.emplace_back(child[j]);
                    j++;
                }
                else{
                    result.emplace_back(father[i]);
                    i++;
                }
            }
            else{
                if(father[i] > child[j]){
                    result.emplace_back(child[j]);
                    j++;
                }
                else{
                    if(strcmp(S+child[j],S+father[i])<0){
                        result.emplace_back(child[j]);
                        j++;
                    }
                    else{
                        result.emplace_back(father[i]);
                        i++;
                    }
                }

            }
        }

    }

    while(j<child.size()){
        result.emplace_back(child[j]);
        j++;
    }

    while(i<father.size()){
        result.emplace_back(father[i]);
        i++;
    }

    return result;
}

std::vector<int> in_prefix_merge_bit_vector_7(const char* S, vector<int> icfl_list, int icfl_list_size, vector<int> father, vector<int> child,vector<int> is_custom_suffix){
    std::vector<int> result;
    result.reserve(father.size()+child.size());

    int i=0,j=0,temp_res;

    //cout<<" last:"<<icfl_list[icfl_list.size()-1]<<" ";

    while( i<father.size() && j<child.size()){
        if(is_custom_suffix[father[i]] && is_custom_suffix[child[j]]){
            //cout<<i<<" "<<j<<"\n";
            temp_res = strcmp(S+child[j],S+father[i]);
            if(temp_res<0) result.emplace_back(child[j++]);
            else result.emplace_back(father[i++]);
        }
        //A questo punto solo uno o nessuno dei due è arificiale
        //Se il primo è artificiale allora si inverte la regola
        else if (is_custom_suffix[father[i]]){
            if(father[i] >= icfl_list[icfl_list_size-1] && child[j] >= icfl_list[icfl_list_size-1]) result.emplace_back(child[j++]);
            else if(get_factor(icfl_list,father[i])==get_factor(icfl_list,child[j])) result.emplace_back(father[i++]);
            else{
                if(father[i] >= icfl_list[icfl_list_size-1]) result.emplace_back(child[j++]);
                else if(child[j] >= icfl_list[icfl_list_size-1]){
                    if(strcmp(S+child[j],S+father[i])<0) result.emplace_back(father[i++]);
                    else result.emplace_back(child[j++]);
                }
                else{
                    if(father[i] > child[j]) result.emplace_back(father[i++]);
                    else{
                        //Questo uguale all'originale, c'è la strcmp 
                        if(strcmp(S+child[j],S+father[i])<0) result.emplace_back(child[j++]);
                        else result.emplace_back(father[i++]);
                    }

                }
            }
        }
        //Se nessuno dei due è custom:
        else if(father[i] >= icfl_list[icfl_list_size-1] && child[j] >= icfl_list[icfl_list_size-1]) result.emplace_back(father[i++]);
        else if(get_factor(icfl_list,father[i])==get_factor(icfl_list,child[j])) result.emplace_back(child[j++]);
        else{
            if(father[i] >= icfl_list[icfl_list_size-1]) result.emplace_back(father[i++]);
            else if(child[j] >= icfl_list[icfl_list_size-1]){
                if(strcmp(S+child[j],S+father[i])<0) result.emplace_back(child[j++]);
                else result.emplace_back(father[i++]);
            }
            else{
                if(father[i] > child[j]) result.emplace_back(child[j++]);
                else{
                    if(strcmp(S+child[j],S+father[i])<0) result.emplace_back(child[j++]);
                    else result.emplace_back(father[i++]);
                }

            }
        }

    }

    while(j<child.size()) result.emplace_back(child[j++]);

    while(i<father.size()) result.emplace_back(father[i++]);

    return result;
}

void in_prefix_merge_bit_vector_8(const char* S, vector<int>& icfl_list, int icfl_list_size, vector<int>& father, int child,vector<int>& is_custom_suffix,int father_lenght,vector<int>& factor_list){

    int i=0,j=0,temp_res;
    bool flag=father[i];

    //cout<<" last:"<<icfl_list[icfl_list.size()-1]<<" ";

    while( i<father.size() && flag){
        if(is_custom_suffix[father[i]] && is_custom_suffix[child]){
            //cout<<i<<" "<<j<<"\n";
            temp_res = strcmp(S+child+father_lenght,S+father[i]+father_lenght);
            if(temp_res<0) flag=false;
            else ++i;
        }
        //A questo punto solo uno o nessuno dei due è arificiale
        //Se il primo è artificiale allora si inverte la regola
        else if (is_custom_suffix[father[i]]){
            if(father[i] >= icfl_list[icfl_list_size-1] && child >= icfl_list[icfl_list_size-1]) flag=false;
            else if(factor_list[father[i]]==factor_list[child]) ++i;
            else{
                if(father[i] >= icfl_list[icfl_list_size-1]) flag=false;
                else if(child >= icfl_list[icfl_list_size-1]){
                    if(strcmp(S+child+father_lenght,S+father[i]+father_lenght)<0) ++i;
                    else flag=false;
                }
                else{
                    if(father[i] > child) ++i;
                    else{
                        //Questo uguale all'originale, c'è la strcmp 
                        if(strcmp(S+child+father_lenght,S+father[i]+father_lenght)<0) flag=false;
                        else ++i;
                    }

                }
            }
        }
        //Se nessuno dei due è custom:
        else if(father[i] >= icfl_list[icfl_list_size-1] && child >= icfl_list[icfl_list_size-1]) ++i;
        else if(factor_list[father[i]]==factor_list[child]) flag=false;
        else{
            if(father[i] >= icfl_list[icfl_list_size-1]) ++i;
            else if(child >= icfl_list[icfl_list_size-1]){
                if(strcmp(S+child+father_lenght,S+father[i]+father_lenght)<0) flag=false;
                else ++i;
            }
            else{
                if(father[i] > child) flag=false;
                else{
                    if(strcmp(S+child+father_lenght,S+father[i]+father_lenght)<0) flag=false;
                    else ++i;
                }

            }
        }

    }

    if(!flag) father.insert(father.begin()+i,child);
    else father.push_back(child);
}


std::vector<int> in_prefix_merge_bit_vector_9(const char* S, vector<int>& icfl_list, int icfl_list_size, vector<int>& father, vector<int>& child,vector<int>& is_custom_suffix,int father_lenght,vector<int>& factor_list){
    std::vector<int> result;
    result.resize(father.size()+child.size());
    int i=0,j=0,temp_res;

    while( i<father.size() && j<child.size()){
        
        if(is_custom_suffix[father[i]] && is_custom_suffix[child[j]]){
            temp_res = strcmp(S+child[j]+father_lenght,S+father[i]+father_lenght);
            if(temp_res<0) {result.at(i+j)=child[j];++j;}
            else {result.at(i+j)=father[i];++i;}
        }
        //A questo punto solo uno o nessuno dei due è arificiale
        //Se il primo è artificiale allora si inverte la regola
        else if (is_custom_suffix[father[i]]){
            if(father[i] >= icfl_list[icfl_list_size-1] && child[j] >= icfl_list[icfl_list_size-1]) {result.at(i+j)=child[j];++j;}
            else if(factor_list[father[i]]==factor_list[child[j]]) {result.at(i+j)=father[i];++i;}
            else{
                if(father[i] >= icfl_list[icfl_list_size-1]) {result.at(i+j)=child[j];++j;}
                else if(child[j] >= icfl_list[icfl_list_size-1]){
                    if(strcmp(S+child[j]+father_lenght,S+father[i]+father_lenght)<0) {result.at(i+j)=father[i];++i;}
                    else {result.at(i+j)=child[j];++j;}
                }
                else{
                    if(father[i] > child[j]) {result.at(i+j)=father[i];++i;}
                    else{
                        //Questo uguale all'originale, c'è la strcmp 
                        if(strcmp(S+child[j]+father_lenght,S+father[i]+father_lenght)<0) {result.at(i+j)=child[j];++j;}
                        else {result.at(i+j)=father[i];++i;};
                    }

                }
            }
        }
        //Se nessuno dei due è custom:
        else if(father[i] >= icfl_list[icfl_list_size-1] && child[j] >= icfl_list[icfl_list_size-1]) {result.at(i+j)=father[i];++i;}
        else if(factor_list[father[i]]==factor_list[child[j]]) {result.at(i+j)=child[j];++j;}
        else{
            if(father[i] >= icfl_list[icfl_list_size-1]) {result.at(i+j)=father[i];++i;}
            else if(child[j] >= icfl_list[icfl_list_size-1]){
                if(strcmp(S+child[j]+father_lenght,S+father[i]+father_lenght)<0) {result.at(i+j)=child[j];++j;}
                else {result.at(i+j)=father[i];++i;};
            }
            else{
                if(father[i] > child[j]) {result.at(i+j)=child[j];++j;}
                else{
                    if(strcmp(S+child[j]+father_lenght,S+father[i]+father_lenght)<0) {result.at(i+j)=child[j];++j;}
                    else {result.at(i+j)=father[i];++i;}
                }

            }
        }

    }
    
    while(j<child.size()) {result.at(i+j)=child[j];++j;}
    while(i<father.size()) {result.at(i+j)=father[i];++i;}

    return result;
}
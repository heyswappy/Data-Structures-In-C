template class<class T1, class T2>
class PriorityQ{
    public:
    vector<T1> key;
    vector<T2> data;
    int last;
    PriorityQ(){last = -1;}
    void perUp(int a);
    void perDown(int a);
    void insert(int a, int b);
    int pop();
};

void PriorityQ :: perUp(int ind){
    int p = (ind-1)/2;
    if(ind<0) return;
    if(p<0) return;
    if (key[p] > key[ind]){
        T1 t = key[p];
        key[p] = key[ind];
        key[ind] = t;
        T2 s = data[p];
        data[p] = data[ind];
        data[ind] = s;
    }
    return;
}

void PriorityQ :: perDown(int ind){
    int max=-1;
    int c1,c2;
    c1 = ind*2;
    c2 = c1+1;
    if((c1<last)&&(key[c1]>key[ind])){
        max = c1;
    }
    if((c2<last)&&(key[c2]>key[ind])){
        max = c2;
    }
    if(max!=-1){
       return perDown(max);
    }
    return;
}

void PriorityQ :: insert(T1 k, T2 d){
    last++;
    key[last] = k;
    data[last] = d;
    perUp(last);
    return;
}

T2 PriorityQ :: pop(){
    T2 t = data[0];
    int a,b;
    if(last<0){
        return -1;
    }
    key[0] = key[last];
    data[0] = data[last];
    last--;
    perDown(0);
    return t;
}
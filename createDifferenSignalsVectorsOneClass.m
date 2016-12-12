%% findqrs
%R to macierz ann dla danego sygnalu danej klasy, ktore trzeba odpalic dla
%kazdej klasy w kazdym sygnale
n=3;
RN={ann105N,ann106N,ann114N};
RVE={ann105VE,ann106VE,ann114VE};
RSV={0,0,ann114SV};

[QsVE,SsVE,RsVE]=findqrs(RVE,Fs,n); 
[QsN,SsN,RsN]=findqrs(RN,Fs,n);
[QsSV,SsSV,RsSV]=findqrs(RSV,Fs,n);

signals={sig105,sig106,sig114};

%% VE
N=n;
class=VE;
for i=1:N %iteracja po kole
    
    signal=signals{1,i};
    
    for j=1:length(QsVE)
        if QsVE(i,j)>0
           
            %i to kolejny sygnal w strukturze i kolejny wiersz w macierzach
            %j to kolejne probki czy kolejne za?amki QRS
            
            Q=QsVE(i,j); %indeks Q
            S=SsVE(i,j); %indeks S
            R=RsVE(i,j); %indeks R
            
            %[A,B]=funckja_ksztaltu(signal,Q,S,R);
            %[C,D]=funckja_ksztaltu2(signal,Q,S,R);
             j   
             
             %klasa(j,:)=[A,B,C,D]
             
        end
        
        
        
    end
end



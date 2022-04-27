
#include <iostream>

using namespace std;

int main()
{
    int n;
    float sumwt=0.0,sumtat=0.0;
    cout<<"Enter the number of process: "<<endl;
    cin>>n;
    
    struct process{
int pid,processtype,BrustTime,ArrivalTime,Priority,TimeQuantum,WaitingTime,TurnAroundTime,ComplitionTime;
};

    struct process p[100];
     
    int bt[n],pr1[n],compt[100],wt[n],tat[n],temp1,temp2,temp3,pid1[n];
    cout<<"Enter pid for the process: "<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>pid1[i];
        
    }
    cout<<"Enter the burn  time in the process: "<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>bt[i];
        
    }
    cout<<"Enter the priority in the process: "<<endl;
    for(int i=0;i<n;i++)
    {
        cin>>pr1[i];
       
    }
//sorting base on priority
for(int i=0;i<n;i++)
{
    for(int j=i+1;j<n;j++)
    {
        if(pr1[i]>pr1[j])
        {
            temp1=bt[i];
            bt[i]=bt[j];
            bt[j]=temp1;
            temp2=pr1[i];
            pr1[i]=pr1[j];
            pr1[j]=temp2;
            temp3=pid1[i];
            pid1[i]=pid1[j];
            pid1[j]=temp3;
            
        }
    }
}

compt[0]=bt[0];
wt[0]=0;
for(int i=1;i<n;i++)
{
compt[i]=bt[0]+compt[i-1];
p[i].ComplitionTime=compt[i];
}
for(int i=0;i<n;i++)
{
    p[i].Priority=pr1[i];
    p[i].BrustTime=bt[i];
    p[i].ComplitionTime=compt[i];
    p[i].pid=pid1[i];
}
for(int i=0;i<n;i++)
{
    tat[i]=compt[i];
    p[i].TurnAroundTime=tat[i];
    wt[i]=tat[i]-bt[i];
    p[i].WaitingTime=wt[i];
    sumtat+=tat[i];
    sumwt+=wt[i];
}
cout<<" pid  Priority   Brust Time    Waiting Time    Turn Around Time "<<endl;
for(int i=0;i<n;i++)
{
    cout<<" "<<p[i].pid<<"\t  "<<p[i].Priority<<"\t   "<<p[i].BrustTime<<"\t\t  "<<p[i].WaitingTime<<"\t\t  "<<p[i].TurnAroundTime<<endl;
}
/*p[4].awt1=sumwt/n;
p[4].atat1=sumtat/n;
cout<<"Total waiting time: "<<sumwt<<endl;
cout<<"Average waiting time: "<<p[4].awt1<<endl;
cout<<"Total turm around time : "<<p[4].ttat1<<endl;
cout<<"Average turn around time: "<<p[4].atat1<<endl;
*/
    return 0;
}


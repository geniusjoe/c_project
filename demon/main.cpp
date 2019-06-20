#include <iostream>

using namespace std;

#define MAXM    500000

int buf1[MAXM],buf2[(200+5)*(200+5)];
int prefix_sum[200+5][200+5][1000+5];
int prefix_num[200+5][200+5][1000+5];

int R,C,M;

struct question{
    int start_x,start_y,end_x,end_y,min_page;
}questions[200000+5];

vlid init(){
    cin>>R>>C>>M;
    if(R==1) for(int i=1;i<=C;i++) cin>>buf1[i];
    else    for(int i=1;i<=R;i++){
        for(int j=1;j<=C;j++){
            cin>>buf[i][j];
        }
    }

    for(int i=1;i<=M;i++) cin>>questions[i].start_x>>questions[i].start_y>>
        questions[i].end_x>>questions[i].end_y>>questions[i].min_page;

    if(R==1){


    }
}

void work1(){



}




int main()
{
    init();

    if(R==1) work1();
    else work2();

}

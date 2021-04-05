/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
import java.util.*;
import java.io.*;


public class Main
{
    static int R,C,M;
    static class Shark{
        int s,d,z;
        Shark(int s,int d,int z){
            this.s = s;
            this.d = d;
            this.z = z;
        }
    }
    static Shark [][] arr = new Shark[100][100];
    
    static int [] dr = {-1,1,0,0};
    static int [] dc = {0,0,1,-1};
    
    
	public static void main(String[] args) throws IOException {
	    BufferedReader br =  new BufferedReader(new InputStreamReader(System.in)); // 한 줄을 읽어오는 클래스 
	    Scanner sc =  new Scanner(System.in); // 2차원 배열을 입력 받을 때 사용하는 스캐너 읽어서 입력받을 때
	   
	    String [] line = br.readLine().split(" "); // 한줄을 읽어 온다.
	    
	    R = Integer.parseInt(line[0]); // 정수형으로 바꿔준다.
	    C = Integer.parseInt(line[1]);
	    M = Integer.parseInt(line[2]);
	    for(int i=0;i<M;++i){
	        String [] str = br.readLine().split(" ");
	        
	        int r = Integer.parseInt(str[0]); // 한 줄에서 입력받으면 차례로 인덱스 순서로 입력받는다.
	        int c = Integer.parseInt(str[1]);
	        int s = Integer.parseInt(str[2]);
	        int d = Integer.parseInt(str[3]);
	        int z = Integer.parseInt(str[4]);
	        --r;
	        --c;
	        --d;
	        arr[r][c] = new Shark(s,d,z);
	        
	    }
	    System.out.print(solve());
	    
	}
	static int solve(){
	    //얕은 복사는 해당 주소를 가리켜서 그 값을 변경시킬 위험이 있다 그래서 깊은 복사를 통해서 완전 똑같은 따로 배열을 복사하는 것이 맞다.
	    Shark [][] backup = new Shark[100][100]; //객체배열의 깊은 복사는 일일이 복사하는 것이 맞다. 
	    int sum = 0;
	    for(int i=0;i<C;++i){
	        for(int j=0;j<R ;++j){
	            if(arr[j][i] != null){ // 자바에서는 null 이 가능하다.
	                sum += arr[j][i].z;
	                arr[j][i] = null;
	                break;
	            }
	        }
	        for(int y=0;y<R;++y){
	            for(int x=0;x<C;++x){
	                backup[y][x] = arr[y][x];
	                arr[y][x] = null;// 깊은 복사와 동시에 원본은 0으로 전부 리셋시켜줘서 비워준다 새로운 이동을 저장하기 위해 
	            }
	        }
	        for(int t=0;t<R;++t){
	            for(int k=0;k<C;++k){
	                Shark cur = backup[t][k];
	                if(cur != null ){
	                    int nr = t + cur.s * dr[cur.d];
	                    int nc = k + cur.s * dc[cur.d];
	                    if(nr<0){
	                        nr = -nr;
	                        cur.d = 1;
	                    }
	                    if(nr>=R){   // 위의 조건은 이 조건문을 실행시키기위한 전제 조건이다 위의 조건문이 만족안해도 이걸 실행하고 위의 조건문을 만족해도 이조건문을 실행시켜야한다.
	                        int a = nr/(R-1);
	                        int b = nr%(R-1);
	                        if(a%2==0){
	                            nr = b;
	                        }
	                        else {
	                            nr = R-1 - b;
	                            cur.d = 0;
	                        }
	                    }
	                    if(nc<0){
	                        nc = -nc;
	                        cur.d = 2;
	                    }
	                    if(nc>=C){
	                        int a = nc/(C-1);
	                        int b = nc%(C-1);
	                        if(a%2==0){
	                            nc = b;
	                        }
	                        else {
	                            nc = C-1 - b;
	                            cur.d = 3;
	                        }
	                    }
	                    if(arr[nr][nc] == null || (arr[nr][nc] != null && arr[nr][nc].z < cur.z)){
	                        arr[nr][nc] = cur;
	                    }
	                }
	
	            }
	        }
	    }
	    return sum;
	}
}





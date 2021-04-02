/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
import java.util.*;

public class Main
{
    static int N;
    static int M[][] = new int[20][20];
    static final int INF = 987654321;
    static int dr[] =  {0,0,-1,1};
    static int dc[]  = {1,-1,0,0};
    static class Point {
        int r,c,d;
        Point(int r,int c,int d){
            this.r = r;
            this.c = c;
            this.d = d;
        }
    }
    static int solve(int r,int c){
        int ret =0;
        int size = 2,cnt = 2;
        Point minPt = new Point(r,c,0);
        do{ //물고기를 찾고 나면 새로운 물고기를 찾으러 가기 위해 리셋팅한다.
            Queue<Point> myque = new LinkedList<Point>();
            boolean visited[][] = new boolean[20][20];
            myque.add(new Point(minPt.r,minPt.c,0));
            visited[minPt.r][minPt.c] = true;
            minPt.d = INF;
            while(myque.peek() != null){
                Point cur  = myque.poll();
                if(cur.d > minPt.d) break;
                if(M[cur.r][cur.c] > size)continue;
                else if(M[cur.r][cur.c] != 0 && M[cur.r][cur.c] < size){
                    if(cur.d < minPt.d){
                        minPt = cur;
                    }
                    else if(cur.d == minPt.d ){
                       if(cur.r < minPt.r){
                           minPt = cur;
                       }
                       else if(cur.r == minPt.r && cur.c < minPt.c){
                          minPt = cur;
                       }
                    }
                    continue; // 머가 문제냐....
                }
                
                
                for(int i=0;i<4;i++){
                    int nr = cur.r + dr[i];
                    int nc = cur.c + dc[i];
                    if(nr < 0 || nr >= N || nc < 0 || nc >= N)continue;
                    if(visited[nr][nc])continue;
                    visited[nr][nc] = true;
                    myque.add(new Point(nr,nc,cur.d+1));
                }
            }
            if(minPt.d != INF){
                ret+=minPt.d;
                --cnt;
                
                if(cnt == 0){
                    ++size;
                    cnt = size;
                }
            }
            M[minPt.r][minPt.c] = 0;
            
        }while(minPt.d != INF);
        
        return ret;
    }
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		N = sc.nextInt();
		int srow = 0, scol = 0;
		for(int i=0;i<N;i++){
		    for(int j=0;j<N;j++){
		        M[i][j] = sc.nextInt();
		        if(M[i][j] == 9){
		            srow = i;
		            scol = j;
		            M[i][j] = 0;
		        }
		    }
		}
		
		
		System.out.println(solve(srow,scol));
	}
}



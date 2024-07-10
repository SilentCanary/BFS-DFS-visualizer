#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <queue>
#define barrier 178  //178
#define cursor 254
#define box_width 60
#define box_height 20
#define UP 72
#define DOWN 80
#define LEFT 75
#define tab 9
#define RIGHT 77
#define space ' '

using namespace std;
int start_x=-1;
int start_y=-1;
int end_x=-1;
int end_y=-1;
vector<vector<int>>grid(box_height,vector<int>(box_width,0)); //to store barriers  and everything

void gotoxy(int x, int y)
{
    fflush(stdout);
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_walls()
{
    system("cls");
    char a = barrier;
    for (int i = 0; i < box_width; i++)
    {
        gotoxy(i, 0);
        cout << "-";
        gotoxy(i, box_height);
        cout << "-";
    }
    for (int i = 1; i < box_height; i++)
    {

        gotoxy(0, i);
        cout << "-";
        gotoxy(box_width, i);
        cout << "-";
    }
}

void draw_barrier()
{
    int x = box_width / 2, y = box_height / 2;
    gotoxy(box_width / 2, box_height / 2);
    char a = barrier;

    while (true)
    {
        if (kbhit())
        {
            char ch = getch();
            switch (ch)
            {
            case UP:
                if (y > 1)
                {
                    y--;
                    gotoxy(x, y);
                    cout << a;
                    grid[y][x]=1;
                }
                break;
            case DOWN:
                if (y < box_height - 2)
                {
                    y++;
                    gotoxy(x, y);
                    cout << a;
                    grid[y][x]=1;
                }
                break;
            case LEFT:
                if (x > 1)
                {
                    x--;
                    gotoxy(x, y);
                    cout << a;
                    grid[y][x]=1;
                }
                break;
            case RIGHT:
                if (x < box_width - 1)
                {
                    x++;
                    gotoxy(x, y);
                    cout << a;
                    grid[y][x]=1;
                }
                break;
            case space:
                return;
            }
        }
        else gotoxy(x,y);
    }
}

vector<pair<int,int>>dfs(vector<vector<int>>&visited,vector<vector<pair<int,int>>>&parent,int x,int y)
{
    visited[y][x]=1;
    int dx[4]={-1,0,1,0};
    int dy[4]={0,1,0,-1};
    if(x==end_x && y==end_y)
    {
        vector<pair<int,int>>path;
        while(x!=start_x || y!=start_y)
        {
            path.push_back({x,y});
            int prev_x=parent[y][x].first;
            int prev_y=parent[y][x].second;
            x=prev_x;
            y=prev_y;
        }
        //path.push_back({start_x,start_y});
        reverse(path.begin(),path.end());
        return path;
    }
    for(int i=0;i<4;i++)
    {
        int new_x=x+dx[i];
        int new_y=y+dy[i];
        if(new_x>=0 && new_x<grid[0].size() && new_y>=0 && new_y<grid.size() && !visited[new_y][new_x] && grid[new_y][new_x]==0)
        {
            parent[new_y][new_x]={x,y};
            vector<pair<int,int>>path=dfs(visited,parent,new_x,new_y);
            if(!path.empty()) return path;
        }
    }
    return {};
}

vector<pair<int,int>>bfs()
{
    
    vector<vector<int>>visited(box_height,vector<int>(box_width,0));
    vector<vector<pair<int,int>>>parent(box_height,vector<pair<int,int>>(box_width,{0,0}));
    queue<pair<int,int>>q;
    //avoiding usage of priority_queue here becuz the distance in all 4 directions are typically same
    //priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
    q.push({start_x,start_y});
    visited[start_y][start_x]=1;
    int dx[4]={-1,0,1,0};
    int dy[4]={0,1,0,-1};
    // int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    // int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    while(!q.empty())
    {   
        int x=q.front().first;
        int y=q.front().second;
        q.pop();
        if(x==end_x && y==end_y)
        {
            vector<pair<int,int>>path;
            while (x!=start_x || y!=start_y)
            {
                path.push_back({x,y});
                int prev_x=parent[y][x].first;
                int prev_y=parent[y][x].second;
                x=prev_x;
                y=prev_y;
            }
            reverse(path.begin(),path.end());
            return path;
            
        }
        //  for(int i=0;i<8;i++)
        // {
        //     int new_x=x+dx[i];
        //     int new_y=y+dy[i];
        //     if(new_x>=0 && new_x<grid[0].size() && new_y>=0 && new_y<grid.size() && !visited[new_y][new_x] && grid[new_y][new_x]==0)
        //     {
        //         visited[new_y][new_x]=1;
        //         parent[new_y][new_x]={x,y};
        //         q.push({new_x,new_y});
        //     }
        // }
        for(int i=0;i<4;i++)
        {
            int new_x=x+dx[i];
            int new_y=y+dy[i];
            if(new_x>=0 && new_x<grid[0].size() && new_y>=0 && new_y<grid.size() && !visited[new_y][new_x] && grid[new_y][new_x]==0)
            {
                visited[new_y][new_x]=1;
                parent[new_y][new_x]={x,y};
                q.push({new_x,new_y});
            }
        }
    }
    return {};
}

void draw_cursor(int color_code)
{
    gotoxy(box_width/2,box_height/2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color_code);
    char a=cursor;
    int x = box_width / 2;
    int y = box_height / 2;
    int dx = 0;
    int dy = 0;
    while (true)
    {
        if (kbhit())
        {
            char ch = getch();
            switch (ch)
            {
            case UP:
                dy=-1;
                dx=0;
                break;
            case DOWN:
                dy=1;
                dx=0;
                break;
            case LEFT:
                dx=-1;
                dy=0;
                break;
            case RIGHT:
                dx=1;
                dy=0;
                break;
            case space:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                start_x=x;
                start_y=y;
                return;
            case tab:
                 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
                end_x=x;
                end_y=y;
                return;
                 
            }
        }
        gotoxy(x, y);
        cout <<" ";
        x += dx;
        y += dy;
        if (x >= box_width-1 || x <= 1)
        {
            dx *= -1;
            x+=dx;
        }
        if (y >= box_height-1 || y <= 1)
        {
            dy *= -1;
            y+=dy;
        }
        gotoxy(x, y);
        fflush(stdout);
        cout << a;
        gotoxy(0,0);
        Sleep(200);
    
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

void draw_path(vector<pair<int,int>>&path,int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
    for(auto it:path)
    {
        gotoxy(it.first,it.second);
        // gotoxy(70,30);
        // cout<<it.first<<" "<<it.second;
        cout<<"*";
        Sleep(50);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

int main()
{
    draw_walls();
    draw_barrier();
    draw_cursor(12);
    draw_cursor(10);
    gotoxy(65,10);
    cout<<"enter an algorithm :"<<endl;
    gotoxy(65,11);
    cout<<"1)BFS   2)DFS"<<endl;
    int ch;
    gotoxy(65,12);
    cin>>ch;
    gotoxy(65,12);
    cout<<"Press any key to continue...";
    getch();
    if(ch==1)
    {
    vector<pair<int,int>>path=bfs();
    draw_path(path,14);
    }
    else
    {
    vector<vector<int>>visited(box_height,vector<int>(box_width,0));
    vector<vector<pair<int,int>>>parent(box_height,vector<pair<int,int>>(box_width,{0,0}));
    vector<pair<int,int>>path2=dfs(visited,parent,start_x,start_y);
    draw_path(path2,9);
    }
    return 0;
}

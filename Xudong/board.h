/*
 *File: <hw6.3>
 *Author: <XUdong yUAn>
 *Created on: <12/1/16>
 *Description:
 *	
 */ 
#ifndef BOARD_H
#define BOARD_H
#include <iostream>

namespace main_savitch_14
{
	class board{
		public:
		board(){
			for(int i = 1; i <= 8; i++){
				for(int j = 1; j <= 8; j++){
					b[i][j]=-1;
				}
			}
			b[4][4]=1;
			b[5][5]=1;
			b[4][5]=2;
			b[5][4]=2;
			int i=0;
			int j=0;
			for(j=0;j<10;j++)
			b[i][j]=0;
			 j=0;
			for( i=0;i<10;i++)
			b[i][j]=0;
			 i=9;
			for( j=0;j<10;j++)
			b[i][j]=0;
			 j=9;
			for( i=0;i<10;i++)
			b[i][j]=0;
			}
			int get_horizontal(){
			return horizontal;
			}
			int get_vertical(){
			return vertical;
			}
			int get_board(int i,int j){
			return b[i][j];
			}
			void flip(int j,int k, int i){
			b[j][k]=i;
			}
		
			bool is_empty(int i,int j){
				return b[i][j]==-1;
			}
			bool is_black(int i,int j){
				return b[i][j]==2;
			}
			bool is_white(int i,int j){
				return b[i][j]==1;
			}
		private:
		static const size_t horizontal = 10;
		static const size_t vertical = 10;
		int b[horizontal][vertical];
	};
}
#endif

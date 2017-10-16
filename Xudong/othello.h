/*
 *File: <hw6.3>
 *Author: <XUdong yUAn>
 *Created on: <12/1/16>
 *Description:
 *	
 */ 
#ifndef OTHELLO_H
#define OTHELLO_H
#include "game.h"
#include "board.h"
#include "colors.h"

using namespace std;
namespace main_savitch_14{
class othello:public game{
	public:
		othello();
		~othello();
		othello(const othello& other);
		void restart();
		game* clone()const;
		int change_int(char c)const;
		int change(char c)const;
		void make_move(const std::string& move);
		bool is_legal(const string& move)const;
		void display_status()const;
		void display_message(const string& message)const;
		void flip_piece(int a,int b,int c,int d);
		int evaluate()const;
		void compute_moves(std::queue<std::string>& moves)const;
		bool is_game_over()const;
		bool right_legal(int a,int b,int c,int d)const;
		bool left_legal(int a,int b,int c,int d)const;
		bool up_legal(int a,int b,int c,int d)const;
		bool down_legal(int a,int b,int c,int d)const;
		bool right_up_legal(int a,int b,int c,int d)const;
		bool right_down_legal(int a,int b,int c,int d)const;
		bool left_up_legal(int a,int b,int c,int d)const;
		bool left_down_legal(int a,int b,int c,int d)const;
		bool check_legal(int a,int b,int c,int d)const;
		void is_passing(std::string pass);
		bool human_legal()const;
		bool computer_legal()const;
		bool all_legal()const;
		who winning()const;
	private:
		board* bo;
};
}
#endif

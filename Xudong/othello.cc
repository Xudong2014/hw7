/*
 *File: <hw6.3>
 *Author: <XUdong yUAn>
 *Created on: <12/1/16>
 *Description:
 *	
 */ 
#include "othello.h"
#include <iostream>
#include <stdio.h>

namespace main_savitch_14{
othello::othello(){
	bo=new board;
}
othello::~othello(){
	board*temp;
	temp=bo;
	delete temp;
}

othello::othello(const othello& other){
	bo=new board(*other.bo);
}

void othello::restart(){
	for(int i = 1; i <= 8; i++){
		for(int j = 1; j <= 8; j++){
			bo -> flip(i,j,-1);
		}
	}
	bo -> flip(4,4,1);
	bo -> flip(5,5,1);
	bo -> flip(4,5,2);
	bo -> flip(5,4,2);
	int i=0;
	int j=0;
	for(j=0;j<10;j++)
		bo -> flip(i,j,0);
	j=0;
	for( i=0;i<10;i++)
		bo -> flip(i,j,0);
	i=9;
	for( j=0;j<10;j++)
		bo -> flip(i,j,0);
	 j=9;
	for( i=0;i<10;i++)
		bo -> flip(i,j,0);
	game::restart();
}

game* othello::clone()const{
	return new othello(*this);
}

int othello::change_int(char c)const{
	int d;
	d=int(c-'0');
	return d;
}

int othello::change(char c)const{
	c=toupper(c);
	int d;
	d=int (c-'A');
	d++;
	return d;
}

void othello::make_move(const std::string& move){
	int col, row;
	col=change_int(move[1]);
	row=change(move[0]);
	if(next_mover()==HUMAN){
		flip_piece(col,row,1,2);
	}
	else{
		flip_piece(col,row,2,1);
	}
	game::make_move(move);
	is_passing(move);
}

void othello::display_status()const{

	cout<< YELLOW << "+---+---+---+---+---+---+---+---+---+"<<endl;
	cout<< YELLOW << "|   | A | B | C | D | E | F | G | H |   "<<endl;
	cout<< YELLOW << "+---+---+---+---+---+---+---+---+---+"<<endl;

	for(int i=1;i<=8;i++){
		cout<<YELLOW<<"| "<<YELLOW<<i<<YELLOW<<" |";
		for(int j=1; j<=8;j++){
			if(bo->is_empty(i,j)){
				cout << YELLOW<<"   |";
			}
			else if(bo->is_black(i,j)){
				cout << BLACK << "#" << YELLOW<<"  |";
			}
			else if(bo->is_white(i,j)){
				cout << GREEN << "#" << YELLOW<<"  |";
			}
		}

		cout  <<endl<< YELLOW << "+---+---+---+---+---+---+---+---+---+"<<endl;
	}
//	cout<<BLACK<<"You go first"<<BLUE<<"#"<<endl;
//	cout<<BLACK<<"Enter the location"<<endl;
	if(is_game_over()){
	game::who winner;
	winner=winning();
	if(winner==HUMAN){
		cout<<"Player 1 win"<<endl;
	}
	else if(winner==COMPUTER){
		cout<<"Player 2 win"<<endl;
	}
	else if(winner==NEUTRAL){
		cout<<"They are equal"<<endl;
	}
	}
}

bool othello::is_game_over()const{
	int over=0;
	for(int i=1;i<=8;i++)
		for(int j=1;j<=8;j++){
			if(bo->get_board(i,j)==-1){
				over=over+1;
			}
		}
	if(over==0)
		return true;
	else if(over>0)
		if(all_legal())
		return true;
}	
void othello::display_message(const string& message)const{
	if(message!="Illegal move")
	if(next_mover()==HUMAN){
	cout<<BLACK<<"You are player 1, your color is "<<BLACK<<"#"<<endl;
	game::display_message(message);
	}
	else if(next_mover()==COMPUTER){
	cout<<GREEN<<"You are player 2, your color is "<<GREEN<<"#"<<endl;
	game::display_message(message);
	}
}

void othello::flip_piece(int a,int b,int c,int d){
	bo->flip(a,b,d);
	if(down_legal(a,b,c,d)){
		for(int i=a+1;bo->get_board(i,b)!=d;i++)
		bo->flip(i,b,d);
	}
	if(up_legal(a,b,c,d)){
		for(int i=a-1;bo->get_board(i,b)!=d;i--)
		bo->flip(i,b,d);
	}
	if(left_legal(a,b,c,d)){
		for(int i=b-1;bo->get_board(a,i)!=d;i--)
		bo->flip(a,i,d);
	}
	if(right_legal(a,b,c,d)){
		for(int i=b+1;bo->get_board(a,i)!=d;i++)
		bo->flip(a,i,d);
	}
	
	if(left_down_legal(a,b,c,d)){
		for(int i=a+1,j=b-1;bo->get_board(i,j)!=d;i++,j--)
		bo->flip(i,j,d);
	}
	if(left_up_legal(a,b,c,d)){
		for(int i=a-1,j=b-1;bo->get_board(i,j)!=d;i--,j--)
		bo->flip(i,j,d);
	}

	if(right_down_legal(a,b,c,d)){
		for(int i=a+1,j=b+1;bo->get_board(i,j)!=d;i++,j++)
		bo->flip(i,j,d);
	}
	if(right_up_legal(a,b,c,d)){
		for(int i=a-1,j=b+1;bo->get_board(i,j)!=d;i--,j++)
		bo->flip(i,j,d);
	}
}

bool othello::right_legal(int a,int b,int c,int d)const{
	if(bo->get_board(a,b+1)==c){
		int i=a;
		for(int j=b+1;bo->get_board(i,j)!=0&&bo->get_board(i,j)!=-1;j++)
			if(bo->get_board(i,j)==d)
				return true;
	}
}

bool othello::left_legal(int a,int b,int c,int d)const{
	if(bo->get_board(a,b-1)==c){
		int i=a;
		for(int j=b-1;bo->get_board(i,j)!=0&&bo->get_board(i,j)!=-1;j--)
			if(bo->get_board(i,j)==d)
				return true;
	}
}

bool othello::up_legal(int a,int b,int c,int d)const{
	if(bo->get_board(a-1,b)==c){
		int i=b;
		for(int j=a-1;bo->get_board(j,i)!=0&&bo->get_board(j,i)!=-1;j--)
			if(bo->get_board(j,i)==d)
				return true;
	}
}

bool othello::down_legal(int a,int b,int c,int d)const{
	if(bo->get_board(a+1,b)==c){
		int i=b;
		for(int j=a+1;bo->get_board(j,i)!=0&&bo->get_board(j,i)!=-1;j++)
			if(bo->get_board(j,i)==d)
				return true;
	}
}

bool othello::right_up_legal(int a,int b,int c,int d)const{
	if(bo->get_board(a-1,b+1)==c){
		int i=a-1;
		int j=b+1;
		for(i=a-1,j=b+1;(bo->get_board(i,j)!=0)&&(bo->get_board(i,j)!=-1);i--,j++){
			if(bo->get_board(i,j)==d){
			return true;
			}
		}
	}
}

bool othello::right_down_legal(int a,int b,int c,int d)const{
	if(bo->get_board(a+1,b+1)==c){
		int i=a+1;
		int j=b+1;
		for(i=a+1,j=b+1;(bo->get_board(i,j)!=0)&&(bo->get_board(i,j)!=-1);i++,j++)
			if(bo->get_board(i,j)==d)
			return true;
	}
}

bool othello::left_up_legal(int a,int b,int c,int d)const{
	if(bo->get_board(a-1,b-1)==c){
		int i=a-1;
		int j=b-1;
		for(i=a-1,j=b-1;(bo->get_board(i,j)!=0)&&(bo->get_board(i,j)!=-1);i--,j--)
			if(bo->get_board(i,j)==d)
			return true;
	}
}

bool othello::left_down_legal(int a,int b,int c,int d)const{
	if(bo->get_board(a+1,b-1)==c){
		int i=a+1;
		int j=b-1;
		for(i=a+1,j=b-1;(bo->get_board(i,j)!=0)&&(bo->get_board(i,j)!=-1);i++,j--)
			if(bo->get_board(i,j)==d)
			return true;
	}
}

bool othello::check_legal(int a,int b,int c,int d)const{
	if(right_legal(a,b,c,d)||left_legal(a,b,c,d)||up_legal(a,b,c,d)||down_legal(a,b,c,d)||right_up_legal(a,b,c,d)||right_down_legal(a,b,c,d)||left_up_legal(a,b,c,d)||left_down_legal(a,b,c,d))
	return true;
}

void othello::is_passing(std::string pass){
	if(next_mover()==HUMAN){
		if(!human_legal()){
			if(computer_legal()){
				cout<<"Human shoud pass: "<<endl;
				game::make_move(pass);
			}
		}
	}
	else{
		if(!computer_legal()){
			if(human_legal()){
				cout<<"Computer should pass: "<<endl;
				game::make_move(pass);
			}
		}
	}
}

bool othello::human_legal()const{
	int legal=0;
	for(int i=1;i<9;i++)
		for(int j=1;j<9;j++){
			if(bo->get_board(i,j)==-1)
				if(check_legal(i,j,1,2))
					legal++;
		}
		if(legal>0)
		return true;
}

bool othello::computer_legal()const{
	int legal=0;
	for(int i=1;i<9;i++)
		for(int j=1;j<9;j++){
			if(bo->get_board(i,j)==-1)
				if(check_legal(i,j,2,1))
					legal++;
		}
		if(legal>0)
		return true;
}

bool othello::all_legal()const{
	if(!human_legal()&&!computer_legal()){
		return true;
	}
}

game::who othello::winning()const{
	int white=0,black=0;
	for(int i=1;i<=8;i++)
		for(int j=1;j<=8;j++){
			if(bo->get_board(i,j)==2)
			black++;
			else if(bo->get_board(i,j)==1)
			white++;
		}
	if(black<white){
		return COMPUTER;
	}
	else if(white<black){
		return HUMAN;
	}
	else if(black==white){
		return NEUTRAL;
	}
}

bool othello::is_legal(const std::string&move)const{
	if(!isdigit(move[1])){
	return false;
	}
	int row,col=0;
	row=change(move[0]);
	col=change_int(move[1]);
		if(next_mover()==HUMAN){
			if((row>0&&row<9)&&(col>0&&col<9)){
				if(bo->get_board(col,row)==-1){
					if(check_legal(col,row,1,2)){
						return true;
					}
					else{
						cout<<"Illegal move"<< endl;
					}
				}
			}
		}
		else{
			if((row>0&&row<9)&&(col>0&&col<9)){
				if(bo->get_board(col,row)==-1){
					if(check_legal(col,row,2,1)){
						return true;
					}
				}
			}
		}
}


void othello::compute_moves(std::queue<std::string>& moves)const{
	string computer_move="";
	char row='A';
	char col='1';
	for(col='A';col!='I';col++)
		for(row='1';row!='9';row++){
			computer_move="";
			computer_move+=col;
			computer_move+=row;
			if(is_legal(computer_move))
				moves.push(computer_move);
		}
}

int othello::evaluate()const{
	int answer=0;
	if(bo->get_board(1,1)==1)
		answer+=50;
	if(bo->get_board(1,8)==1)
		answer+=50;
	if(bo->get_board(8,1)==1)
		answer+=50;
	if(bo->get_board(8,8)==1)
		answer+=50;
	if(bo->get_board(1,1)==2)
		answer-=50;
	if(bo->get_board(1,8)==2)
		answer-=50;
	if(bo->get_board(8,1)==2)
		answer-=50;
	if(bo->get_board(8,8)==2)
		answer-=50;
	for(int i=1,j=2;j<7;j++)
		if(bo->get_board(i,j)==1)
		answer+=10;
		else if(bo->get_board(i,j)==2)
		answer-=10;
	for(int j=1,i=2;i<7;i++)
		if(bo->get_board(i,j)==1)
		answer+=10;
		else if(bo->get_board(i,j)==2)
		answer-=10;
	for(int i=8,j=2;j<7;j++)
		if(bo->get_board(i,j)==1)
		answer+=10;
		else if(bo->get_board(i,j)==2)
		answer-=10;
	for(int j=8,i=2;i<7;i++)
		if(bo->get_board(i,j)==1)
		answer+=10;
		else if(bo->get_board(i,j)==2)
		answer-=10;
	return answer;
}
}

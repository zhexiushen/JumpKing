#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "King.h"

namespace game_framework {

	King::King()
	{
		Initialize();
	}

	int King::GetX1()
	{
		return x;
	}

	int King::GetY1()
	{
		return y;
	}

	int King::GetX2()
	{
		return x + character.Width();
	}

	int King::GetY2()
	{
		return y + character.Height();
	}

	void King::Initialize()
	{
		const int X_POS = 400;
		const int Y_POS = 545 - 34;
		x = X_POS;
		y = Y_POS;
		isMovingLeft = isMovingRight = isMovingUp = isMovingDown = isCharging = false;
		initial_velocity = velocity = 0;
		floor = Y_POS;
		rising = false;
	}

	void King::LoadBitmap()
	{
		int leftMovement[] = { IDB_KINGLEFTSTAND, IDB_KINGLEFTWALK_1, IDB_KINGLEFTWALK_2, IDB_KINGLEFTWALK_3, 
							   IDB_KINGLEFTRISE, IDB_KINGLEFTFALL, IDB_KINGLEFTSLIP };
		int rightMovement[] = { IDB_KINGRIGHTSTAND, IDB_KINGRIGHTWALK_1, IDB_KINGRIGHTWALK_2, IDB_KINGRIGHTWALK_3,
								IDB_KINGRIGHTRISE, IDB_KINGRIGHTFALL, IDB_KINGRIGHTSLIP };
		for (int i = 0; i < 7; i++) {
			character.AddBitmap(leftMovement[i], RGB(255, 255, 255));
		}
		for (int i = 0; i < 7; i++) {
			character.AddBitmap(rightMovement[i], RGB(255, 255, 255));
		}
		character.AddBitmap(IDB_KINGCHARGE, RGB(255, 255, 255));

		//character.AddBitmap(IDB_KINGLEFTSTAND, RGB(255, 255, 255));
		//character.AddBitmap(IDB_KINGLEFTWALK_1, RGB(255, 255, 255));
		//character.AddBitmap(IDB_KINGLEFTWALK_2, RGB(255, 255, 255));
		//character.AddBitmap(IDB_KINGLEFTWALK_3, RGB(255, 255, 255));
		//character.AddBitmap(IDB_KINGLEFTRISE, RGB(255, 255, 255));
		//character.AddBitmap(IDB_KINGLEFTFALL, RGB(255, 255, 255));
		//character.AddBitmap(IDB_KINGLEFTSLIP, RGB(255, 255, 255));

		//character.AddBitmap(IDB_KINGRIGHTSTAND, RGB(255, 255, 255));
		//character.AddBitmap(IDB_KINGRIGHTWALK_1, RGB(255, 255, 255));
		//character.AddBitmap(IDB_KINGRIGHTWALK_2, RGB(255, 255, 255));
		//character.AddBitmap(IDB_KINGRIGHTWALK_3, RGB(255, 255, 255));
		//character.AddBitmap(IDB_KINGRIGHTRISE, RGB(255, 255, 255));
		//character.AddBitmap(IDB_KINGRIGHTFALL, RGB(255, 255, 255));
		//character.AddBitmap(IDB_KINGRIGHTSLIP, RGB(255, 255, 255));
	}

	void King::OnMove(Map *m)
	{
		const int STEP_SIZE = 6;
		
		if (isCharging) {
			initial_velocity++;
			if (initial_velocity > 21)
				isCharging = false;
			velocity = initial_velocity;
		}
		else {
			if (isMovingLeft) {
				isFacingLeft = true;
				character.OnMoveLeft();
				if (m->isEmpty(x - STEP_SIZE, y))
					x -= STEP_SIZE;
			}
			if (isMovingRight) {
				isFacingLeft = false;
				character.OnMoveRight();
				if (m->isEmpty(GetX2() + STEP_SIZE, GetY2()))
					x += STEP_SIZE;
			}
			if (isMovingUp) {
				if (m->isEmpty(x, y - STEP_SIZE))
					y -= STEP_SIZE;
			}
			if (isMovingDown) {
				if (m->isEmpty(x, GetY2() + STEP_SIZE))
					y += STEP_SIZE;
			}
			initial_velocity = 0;
			if (rising) {
				if (velocity > 0) {
					y -= velocity;
					velocity--;
				}
				else {
					rising = false;
					velocity = 1;
				}
			}
			else {
				if (y < floor - 1) {
					if (m->isEmpty(x, GetY2() + velocity)) {
						y += velocity;
						velocity++;
					}
				}
				else {
					y = floor - 1;
					velocity = initial_velocity;
				}
			}
		}
	}

	void King::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
	}

	void King::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (isMovingLeft) {
			character.SetBitmapNumber(1);
		}
		//if (isMovingLeft && isMovingRight) {
		//	animation.SetBitmapNumber(1);
		//	isMovingLeft = isMovingRight = false;
		//}
		//else if (!isMovingLeft && isMovingRight) {
		//	animation.SetBitmapNumber(5);
		//	isMovingRight = true;
		//	//animation.SetTopLeft(25, y);
		//}
	}

	void King::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (isMovingRight) {
			character.SetBitmapNumber(8);
		}
		//if (isMovingRight && isMovingLeft) {
		//	animation.SetBitmapNumber(0);
		//	isMovingRight = isMovingLeft = false;
		//}
		//else if (!isMovingRight && isMovingLeft) {
		//	animation.SetBitmapNumber(2);
		//	isMovingLeft = true;
		//}
	}

	void King::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void King::SetCharging(bool flag)
	{
		isCharging = flag;
		if (isCharging) {
			character.SetBitmapNumber(8);
			rising = true;
		}
	}

	void King::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}

	void King::OnShow()
	{
		character.SetTopLeft(x, y);
		character.OnShow();
	}

	void King::SetVelocity(int velocity)
	{
		this->velocity = velocity;
		this->initial_velocity = velocity;
	}

	void King::SetFloor(int floor) 
	{
		this->floor = floor;
	}
}
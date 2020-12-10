/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}
TEST(PiezasTest, emptyBoard)
{
	Piezas obj;
	bool result = true;
	for (int i = 0; i < 3; i ++) {
		for (int j = 0; j < 4; j ++) {
			if (obj.pieceAt(i,j) != Blank) {
				result = false;
				i = 3; j = 4;
			}
		}
	}
	ASSERT_TRUE(result);
}
TEST(PiezasTest, dropOnePiece)
{
	Piezas obj;
	obj.dropPiece(3);
	ASSERT_TRUE(obj.pieceAt(0,3) == X);
	ASSERT_TRUE(obj.pieceAt(1,3) == Blank);
}
TEST(PiezasTest, dropTwoPieces)
{
	Piezas obj;
	obj.dropPiece(2); obj.dropPiece(2);
	ASSERT_TRUE(obj.pieceAt(0,2) == X);
	ASSERT_TRUE(obj.pieceAt(1,2) == O);
	ASSERT_TRUE(obj.pieceAt(2,2) == Blank);
}
TEST(PiezasTest, outOfBounds)
{
	Piezas obj;
	Piece p = obj.dropPiece(7);
	ASSERT_TRUE(p == Invalid);
	ASSERT_TRUE(obj.pieceAt(0,7) == Invalid);
}
TEST(PiezasTest, outOfBoundsNegative)
{
	Piezas obj;
	Piece p = obj.dropPiece(-1);
	ASSERT_TRUE(p == Invalid);
	ASSERT_TRUE(obj.pieceAt(0,-1) == Invalid);
}
TEST(PiezasTest, columnFull)
{
	Piezas obj;
	obj.dropPiece(0); obj.dropPiece(0);
	obj.dropPiece(0); Piece p = obj.dropPiece(0);
	ASSERT_TRUE(p == Blank);
	ASSERT_TRUE(obj.pieceAt(3,0) == Invalid);
}
TEST(PiezasTest, belowBoard)
{
	Piezas obj;
	obj.dropPiece(0);
	ASSERT_TRUE(obj.pieceAt(-1,0) == Invalid);
}
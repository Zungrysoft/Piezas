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

#include <aiv_unit_test.h>
#include <utils.h>
//Example
// TEST(name)
// {
// 	ASSERT_THAT(condition);
// }

TEST(max_screen)
{
	vector2_t max = point_to_screen(1,1,600,600);
	ASSERT_THAT(max.x == 600);
}	

TEST(half_screen)
{
	vector2_t half = point_to_screen(0,1,600,600);
	ASSERT_THAT(half.x == 300);
}	

TEST(min_screen)
{
	vector2_t min = point_to_screen(-1,1,600,600);
	ASSERT_THAT(min.x == 0);
}	

TEST(point_max)
{
	vector2_t max = screen_to_point(600,600,600,600);
	ASSERT_THAT(max.x == 1);
}	

TEST(point_half)
{
	vector2_t half = screen_to_point(300,600,600,600);
	ASSERT_THAT(half.x == 0);
}	

TEST(point_min)
{
	vector2_t min = screen_to_point(0,600,600,600);
	ASSERT_THAT(min.x == -1);
}	

TEST(max_screen_ref)
{
	vector2_t max;
	max.x = 1;
	max.y = 1; 
	point_to_screen_ref(&max,600,600);

	ASSERT_THAT(max.x == 600);
}	

TEST(half_screen_ref)
{
	vector2_t half;
	half.x = 0;
	half.y = 1; 
	point_to_screen_ref(&half,600,600);
	
	ASSERT_THAT(half.x == 300);
}	

TEST(min_screen_ref)
{
	vector2_t min;
	min.x = -1;
	min.y = 1; 
	point_to_screen_ref(&min,600,600);
	
	ASSERT_THAT(min.x == 0);
}	

TEST(point_max_ref)
{
	vector2_t max;
	max.x = 600;
	max.y = 600; 

	screen_to_point_ref(&max,600,600);
	ASSERT_THAT(max.x == 1);
}	

TEST(point_half_ref)
{
	vector2_t half;
	half.x = 300;
	half.y = 300; 

	screen_to_point_ref(&half,600,600);
	ASSERT_THAT(half.x == 0);
}	

TEST(point_min_ref)
{
	vector2_t min;
	min.x = 0;
	min.y = 300; 
	screen_to_point_ref(&min,600,600);
	ASSERT_THAT(min.x == -1);
}	

int main(int argc, char **argv)
{
	RUN_TEST(max_screen);
	RUN_TEST(half_screen);
	RUN_TEST(min_screen);
	RUN_TEST(point_max);
	RUN_TEST(point_half);
	RUN_TEST(point_min);
	RUN_TEST(max_screen_ref);
	RUN_TEST(half_screen_ref);
	RUN_TEST(min_screen_ref);
	RUN_TEST(point_max_ref);
	RUN_TEST(point_half_ref);
	RUN_TEST(point_min_ref);
	PRINT_TEST_RESULTS();
	return 0;
}

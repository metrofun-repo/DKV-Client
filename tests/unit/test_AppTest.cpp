#include <gtest/gtest.h>
#include "app/App.h"

TEST(AppPlaceholderTest, PlaceHolderTest) {
    App app({});
    
    app.run();

    EXPECT_EQ(true, true);
}
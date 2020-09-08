#include "test_common.hpp"
#include "action_tapping.h"
#include "layer_with_mod_tap.h"

using testing::_;
using testing::InSequence;

class LayerModHoldTapTest : public TestFixture {
  protected:
    void ExpectActivation(){
      // Noop triggered by layer change.
      ExpectKeys();
      // Expect modifier turned on.
      ExpectKeyPressed(KC_LSFT);
    }

    void ExpectDeactivation(){
      // Expect modifier turned off.
      ExpectKeyReleased(KC_LSFT);
      // Noop triggered by layer change.
      ExpectKeys();
    }

    void ExpectKeys(){
      auto key_matcher = testing::MakeMatcher(new KeyboardReportMatcher(keys));
      EXPECT_CALL(driver, send_keyboard_mock(key_matcher));
    }

    void ExpectKeyReleased(uint8_t key){
      auto it = std::find(keys.begin(), keys.end(), key);
      EXPECT_NE(it, keys.end());
      keys.erase(it);

      ExpectKeys();
    }

    void ExpectKeyPressed(uint8_t key){
      auto it = std::find(keys.begin(), keys.end(), key);
      EXPECT_EQ(it, keys.end());
      keys.push_back(key);

      ExpectKeys();
    }

    void ExpectTap(uint8_t key){
      ExpectKeyPressed(key);
      ExpectKeyReleased(key);
    }

    void ExpectNoMorePresses(){
      EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
    }

    TestDriver driver;
    InSequence s;
    std::vector<uint8_t> keys;
};

enum class Position {
  DOWN,
  UP
};

class ScopedPhysicalKeyPress {
  public:
    explicit ScopedPhysicalKeyPress(LayerModHoldTapTest* test,
        uint8_t col, uint8_t row, Position position):test_(test){
      if(position == Position::DOWN){
        press_key(col, row);
      }
      else {
        release_key(col, row);
      }
    }
    ~ScopedPhysicalKeyPress(){
      test_->run_one_scan_loop();
    }
  private:
    LayerModHoldTapTest* test_;
};


TEST_F(LayerModHoldTapTest, PressingForLessThanTappingTermResultsInTap) {
  {
    ScopedPhysicalKeyPress down(this, 7, 0, Position::DOWN);
    ExpectActivation();
  }

  {
    ScopedPhysicalKeyPress down(this, 7, 0, Position::UP);
    ExpectDeactivation();
    ExpectTap(KC_1);
  }
}

TEST_F(LayerModHoldTapTest, PressingForMoreThanTappingTermResultsIsNoop) {
  // Press the key.
  press_key(7, 0);
  ExpectActivation();

  run_one_scan_loop();

  idle_for(TAPPING_TERM);

  // Then the release
  release_key(7, 0);

  ExpectDeactivation();

  // No tap since release happened outside of
  // tapping term.
  ExpectNoMorePresses();

  run_one_scan_loop();
}

#include "test_common.hpp"
#include "layer_with_mod_tap.h"
#include "action_tapping.h"

using testing::_;
using testing::InSequence;

class LayerModHoldTapTest : public TestFixture {
 protected:
  void ExpectActivation() {
    // Noop triggered by layer change.
    ExpectKeys();
    // Expect modifier turned on.
    ExpectKeyPressed(KC_LSFT);
  }

  void ExpectDeactivation() {
    // Expect modifier turned off.
    ExpectKeyReleased(KC_LSFT);
    // Noop triggered by layer change.
    ExpectKeys();
  }

  void ExpectKeys() {
    auto key_matcher = testing::MakeMatcher(new KeyboardReportMatcher(keys));
    EXPECT_CALL(driver, send_keyboard_mock(key_matcher));
  }

  void ExpectKeyReleased(uint8_t key) {
    auto it = std::find(keys.begin(), keys.end(), key);
    ASSERT_NE(it, keys.end());
    keys.erase(it);

    ExpectKeys();
  }

  void ExpectKeyPressed(uint8_t key) {
    auto it = std::find(keys.begin(), keys.end(), key);
    EXPECT_EQ(it, keys.end());
    keys.push_back(key);

    ExpectKeys();
  }

  void ExpectTap(uint8_t key) {
    ExpectKeyPressed(key);
    ExpectKeyReleased(key);
  }

  void ExpectNoMorePresses() {
    EXPECT_CALL(driver, send_keyboard_mock(_)).Times(0);
  }

  TestDriver driver;
  InSequence s;
  std::vector<uint8_t> keys;
};

enum class Position { DOWN, UP };

class ScopedPhysicalKeyPress {
 public:
  explicit ScopedPhysicalKeyPress(LayerModHoldTapTest* test, uint8_t col,
                                  uint8_t row, Position position)
      : test_(test) {
    assert(test);

    if (position == Position::DOWN) {
      press_key(col, row);
    } else {
      release_key(col, row);
    }
  }
  ~ScopedPhysicalKeyPress() { test_->run_one_scan_loop(); }

 private:
  LayerModHoldTapTest* test_;
};

TEST_F(LayerModHoldTapTest, PressingForLessThanTappingTermResultsInTap) {
  {
    ScopedPhysicalKeyPress down(this, 7, 0, Position::DOWN);
    ExpectActivation();
  }

  {
    ScopedPhysicalKeyPress up(this, 7, 0, Position::UP);
    ExpectDeactivation();
    ExpectTap(KC_ESC);
  }
}

TEST_F(LayerModHoldTapTest, PressingForMoreThanTappingTermResultsInNoop) {
  {
    ScopedPhysicalKeyPress down(this, 7, 0, Position::DOWN);
    ExpectActivation();
  }

  idle_for(TAPPING_TERM + 1);

  {
    ScopedPhysicalKeyPress up(this, 7, 0, Position::UP);
    ExpectDeactivation();
    // No tap since release happened outside of
    // tapping term.
    ExpectNoMorePresses();
  }
}

TEST_F(LayerModHoldTapTest,
       FullInterruptingPressOfTransparentPositionResultsInModdedBaseLayer) {
  {
    ScopedPhysicalKeyPress down(this, 7, 0, Position::DOWN);
    ExpectActivation();
  }

  { ScopedPhysicalKeyPress down(this, 0, 1, Position::DOWN); }

  { ScopedPhysicalKeyPress up(this, 0, 1, Position::UP); }

  {
    ScopedPhysicalKeyPress up(this, 7, 0, Position::UP);
    ExpectTap(KC_A);
    ExpectDeactivation();
  }
}

TEST_F(LayerModHoldTapTest,
       CompletingPressAsInterruptionDuringTappingTermResultsInOriginalPress) {
  {
    ScopedPhysicalKeyPress down(this, 0, 0, Position::DOWN);
    ExpectKeyPressed(KC_Q);
  }

  {
    ScopedPhysicalKeyPress down(this, 7, 0, Position::DOWN);
    ExpectActivation();
  }

  { ScopedPhysicalKeyPress up(this, 0, 0, Position::UP); }

  {
    ScopedPhysicalKeyPress up(this, 7, 0, Position::UP);
    ExpectDeactivation();
    ExpectTap(KC_ESC);
    ExpectKeyReleased(KC_Q);
  }
}

TEST_F(LayerModHoldTapTest,
       FullInterruptingPressDuringTappingTermResultsInModifiedPress) {
  {
    ScopedPhysicalKeyPress down(this, 7, 0, Position::DOWN);
    ExpectActivation();
  }

  { ScopedPhysicalKeyPress down(this, 0, 0, Position::DOWN); }

  { ScopedPhysicalKeyPress up(this, 0, 0, Position::UP); }

  {
    ScopedPhysicalKeyPress up(this, 7, 0, Position::UP);
    ExpectTap(KC_1);
    ExpectDeactivation();
  }
}

TEST_F(LayerModHoldTapTest,
       InterruptingAfterTappingTermResultsInFlushAndModifiedPress) {
  {
    ScopedPhysicalKeyPress down(this, 7, 0, Position::DOWN);
    ExpectActivation();
  }

  // Within tapping term, key is swallowed.
  { ScopedPhysicalKeyPress down(this, 0, 0, Position::DOWN); }

  idle_for(TAPPING_TERM + 1);

  // Outisde tapping term.
  {
    ScopedPhysicalKeyPress down(this, 1, 0, Position::DOWN);

    // Buffered presses are flushed and the latest one is let through.
    ExpectKeyPressed(KC_1);
    ExpectKeyPressed(KC_2);
  }

  // Noop on special key release.
  {
    ScopedPhysicalKeyPress up(this, 7, 0, Position::UP);
    ExpectDeactivation();
  }
}

TEST_F(LayerModHoldTapTest,
       InterruptingTapWithAnIncompleteKeyPressShouldResultsInTapPlusFlush) {
  {
    ScopedPhysicalKeyPress down(this, 7, 0, Position::DOWN);
    ExpectActivation();
  }

  // Within tapping term, key is swallowed.
  { ScopedPhysicalKeyPress down(this, 0, 0, Position::DOWN); }

  {
    ScopedPhysicalKeyPress up(this, 7, 0, Position::UP);
    ExpectDeactivation();

    ExpectTap(KC_ESC);

    // Since layer and mod were cancelled the keycode from the
    // previous layer should be emitted.
    ExpectKeyPressed(KC_Q);
  }
}

#include "test_common.hpp"
#include "action_tapping.h"
#include "layer_with_mod_tap.h"

using testing::_;
using testing::InSequence;

class Tapping : public TestFixture {
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

TEST_F(Tapping, TapA_SHFT_T_KeyReportsKey) {
  // Press the key.
  press_key(7, 0);
  ExpectActivation();

  run_one_scan_loop();

  // Then the release
  release_key(7, 0);

  ExpectDeactivation();

  // Lastly the tap.
  ExpectTap(KC_1);

  run_one_scan_loop();
}

TEST_F(Tapping, TapA_SHFT_T_KeyReportsKey_2) {
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

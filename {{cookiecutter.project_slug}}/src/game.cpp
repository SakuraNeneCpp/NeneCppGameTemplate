// game.cpp
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <stdexcept>
#include <unordered_set>
#include <sstream>
#include <cstdlib>
#include <random>
#include <cmath>
#include <vector>
#include <SDL3/SDL.h>
#include <NeneEngine/NeneNode.hpp>

// ルートノード
class Game final : public NeneRoot {
public:
    Game()
    : NeneRoot(
        "game",
        "ChromeDino",
        960, 540,
        SDL_WINDOW_RESIZABLE,
        100, 100,
        icon_path().c_str()
      )
    {}
protected:
    void init_node() override {
        // シーンスイッチを生成.
        add_child(std::make_unique<SceneSwitch>("scene_switch"));
    }
private:
    static const std::string& icon_path() {
        static std::string p = PathService::resolve_base("assets/icons/T-Rex.svg");
        return p;
    }
};
std::unique_ptr<NeneRoot> create_game() {
    return std::make_unique<Game>();
}
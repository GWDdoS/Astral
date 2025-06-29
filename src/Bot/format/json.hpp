#include <matjson.hpp>

struct Input {
    int player;
    int button;
    bool down;
};

template <>
struct matjson::Serialize<Macro> {
    static geode::Result<Macro> fromJson(const matjson::Value& value) {
        Macro ret;
        for (auto [frame, inputs] : value["actions"]) {
		auto rFrame = geode::utils::numFromString<int>(frame);
		if (rFrame.isErr()) return geode::Err("Failed to get frame: {}", rFrame.unwrapErr());
		std::vector<Input> inputV;
		for (auto input : inputs) {
			Input inp;
			inp.player = input["player"].asInt().unwrapOrDefault();
			inp.button = input["button"].asInt().unwrapOrDefault();
			inp.down = input["down"].asBool().unwrapOrDefault();
			inputV.push_back(inp);
		}
		ret.actions[rFrame.unwrap()] = inputV;
		
	}
        return geode::Ok(ret);
    }
    static matjson::Value toJson(Macro macro) {
        auto ret = matjson::makeObject({
		{"actions", {}}
	});
	for (auto [frame, inputs] : macro.actions) {
		matjson::Value val = matjson::Value().array();
		for (auto input : inputs) {
			auto obj = matjson::makeObject({
				{"player", input.player},
				{"button", input.button},
				{"down", input.down}
			});

			val.push(obj);
		geode::log::info("{}", obj.dump());
		}
		if (val.size() > 0)
		ret["actions"].set(fmt::format("{}", frame), val);
	}	
	return ret;
    }
};
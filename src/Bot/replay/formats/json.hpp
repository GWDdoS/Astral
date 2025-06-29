#include <matjson.hpp>

struct Input {
	int frame
    bool jump;
	int player;
};

template <>
struct matjson::Serialize<Macro> {
    static geode::Result<Macro> fromJson(const matjson::Value& value) {
        Macro ret;
        for (auto [inputs] : value["actions"]) {
			std::vector<Input> inputV;
			for (auto input : inputs) {
				Input inp;
				inp.frame = input["frame"].asInt().unwrapOrDefault();
				inp.jump = input["jump"].asBool().unwrapOrDefault();
				inp.player = input["player"].asInt().unwrapOrDefault();
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
	for (auto [inputs] : macro.actions) {
		matjson::Value val = matjson::Value().array();
		for (auto input : inputs) {
			auto obj = matjson::makeObject({
				{"frame", input.player},
				{"jump", input.jump},
				{"player", input.down}
			});

			val.push(obj);
		geode::log::info("{}", obj.dump());
		}
		if (val.size() > 0)
		ret["actions"].set(fmt::format("{}"), val);
	}	
	return ret;
    }
};
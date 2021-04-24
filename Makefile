REVEAL_JS = third_party/reveal.js
REVEAL_JS_BUILD = $(REVEAL_JS)/dist/reveal.js
GAME = third_party/flame_perfomance_test_game
THIRD_PARTIES = $(REVEAL_JS)/index.html \
								$(GAME)/README.md

build: reveal_js

present: $(REVEAL_JS_BUILD)
	cd $(REVEAL_JS) && npm run start

$(REVEAL_JS_BUILD): $(THIRD_PARTIES)
	cd $(REVEAL_JS) && npm install && npm run build

$(THIRD_PARTIES):
	git submodule init
	git submodule update

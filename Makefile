EXECUTABLE = tem
COMPILER = gcc

help: ## Prints help for targets with comments
	@cat $(MAKEFILE_LIST) | grep -E '^[a-zA-Z_-]+:.*?## .*$$' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

cp: ## Runs the executable
	$(COMPILER) main.c -o $(EXECUTABLE) 

clean: ## Deletes the executable
	rm $(EXECUTABLE)

build: ## Builds the executable
	$(COMPILER) main.c -o $(EXECUTABLE)
	sudo mv $(EXECUTABLE) /usr/bin

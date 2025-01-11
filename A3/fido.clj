;; -------------
;; This is the menu template for the Fido app. You can use it as a starting
;; point for the assignment
;; ------------

;; defines the namespace for the current Clojure file
(ns a3
  ;; imports the clojure.string library, which contains useful functions for string manipulation (like trimming). The alias str is used to refer to this library.
  (:require [clojure.string :as str])
  ;; imports the clojure.java.io library for file input/output operations. The alias io is used to access this library's functions.
  (:require [clojure.java.io :as io])
  ;; imports the food namespace, likely another Clojure file (or module) to access its functions and definitions.
  (:require [food])
) 







;;-------------------
;; THE MENU FUNCTIONS
;; ------------------

;; Display the menu and ask the user for the option
;; Defines a function named showMenu with no parameters.
(defn showMenu []
  ;; Prints the title of the menu with some extra line breaks for spacing.
  (println "\n\n*** Let's Feed Fido ***")
  ;; Prints a separator line for the menu.
  (println     "-----------------------\n")
  ;; Prints option 1 for listing map files.
  (println "1. Display list of map files")
  ;; Prints option 2 for displaying a map.
  (println "2. Display a map for Fido")
  ;; Prints option 3 for exiting the program.
  (println "3. Exit")
  ;; do allows multiple expressions to be executed sequentially.
  (do
    ;; Prints a prompt asking for the user to enter an option.
    (print "\nEnter an option? ")
    ;; Ensures that the prompt is printed to the screen immediately.
    (flush)
    ;; Reads the user's input (the option they chose) as a string.
    (read-line)
  )
)





;; Display all files in the current folder
;; Defines a function named option1 with no parameters.
(defn option1 []
  ;; Check if the file is not a directory
  (let 
    [files (filter #(and (.isFile %)
                      ;; Match only .txt files
                      (re-matches #".*\.txt" (.getName %))
                    )
      ;; Get all files in the current directory
      (file-seq (io/file "."))
      )
    ]
    ;; If no .txt files are found
    (if (empty? files)
      ;; Print a message to notify user that there are no map files found
      (println "No map files found.")
      ;; do allows multiple expressions to be executed sequentially.
      (do
        ;; This prints an empty line
        (println)
        ;; Print a header for the Map List
        (println "Map List:")
        ;; Loop through each file and print its name
        (doseq [file files]
          ;; Print the path of the current file, prefixed with a "*"
          (println (str "*" (.getPath file)))
        )
      )
    )
    ;; Print a prompt message for user interaction
    (println "\nPress any key to continue...")
    ;; Ensures that the prompt is printed to the screen immediately.
    (flush)
    ;; Wait for the user to press any key before continuing  
    (read-line)
  )
)


;; Get the map specified by the user and start looking for the food
;; Defines a function named option2 with no parameters.
(defn option2 []
  ;; Prints a prompt asking for the user to enter a file name.
  (print "\nPlease enter a file name => ")
  ;; Ensures the prompt is printed immediately to the screen.
  (flush)
  ;; Reads the file name entered by the user and stores it in the file_name variable.
  (let [file-name (read-line)]
    ;; Check if the file exists
    (if (.exists (io/file file-name))
      ;; If the file exists, read its content into map-content after trimming whitespace.
      (let [map-content (str/trim (slurp file-name))]
        ;; Prints the title of the challenge
        (println "\nThis is Fido's Challenge:")
        ;; This prints an empty line
        (println)
        ;; Prints the content of the map
        (println map-content)
        ;; Checks if the map is valid
        (if (food/valid-map? map-content)
          ;; If valid, find food in the map using the find-food function
          (let [[found final-map] (food/find-food map-content)]   
            ;; If food is found, print success message, otherwise print failure message   
            (if found
              (println "\nWoo Hoo - Fido found her food")
              (println "\nOh no - Fido could not find her food")
            )
            ;; This prints an empty line
            (println)
            ;; Iterates over the final map and prints each row
            (doseq [row final-map]
              (println row))
          )
          ;; If the map isn't valid, print an error message
          (println "Oops: the map is not valid.")
        )
      )
      ;; If the file doesn't exist, print an error message
      (println (str "Oops: specified file " file-name " does not exist."))
    )
  )
  ;; This prints an empty line
  (println)
  ;; Prints a message prompting the user to press any key to continue
  (println "\nPress any key to continue...")
  ;; Ensures the prompt is printed immediately to the screen.
  (flush)
  ;; Wait for the user to press any key before continuing  
  (read-line)
)


;; If the menu selection is valid, call the relevant function to process the selection
;; Defines a function named processOption that takes a parameter option (the user's selected menu option).
(defn processOption [option]
  ;; Checks if the option is equal to "1" (the first menu option).
  (if( = option "1")
      ;; Calls the option1 function if the user selected "1".
      (option1)
      ;; Otherwise, checks if the option is equal to "2" (the second menu option).
      (if( = option "2")
        ;; Calls the option2 function if the user selected "2".
        (option2)
        ;; If neither "1" nor "2" is selected, prints an "Invalid menu option" message.
        (do
          (println "Invalid menu option...")
          ;; Sleep for 1000 milliseconds (1 second)
          (Thread/sleep 1000)
        )
      )
  )
)


;; Display the menu and get a menu item selection. 
;; Process the selection and then loop again to get the next menu selection
(defn menu
  ;; parm(s) can be provided here, if needed
  []
  ;; Clear the screen (ANSI escape code to clear terminal)
  (println (str (char 27) "[2J" (char 27) "[H"))
  ;; Ensures the prompt is printed immediately to the screen.
  (flush)
  ;; Calls showMenu to display the menu, trims any extra whitespace from the input, and stores the result in option.
  (let [option (str/trim (showMenu))]
    ;; Checks if the user selected "3" (the exit option).
    (if (= option "3")
      ;; If the user selected "3", it prints "Good Bye" and exits the program.
      (println "\nGood Bye\n")
      ;; If the user did not select "3", it processes the selected option.
      (do
        ;; Calls processOption with the user's selected option to execute the corresponding action.
        (processOption option)
        ;; The recur statement calls the menu function again, causing the program to loop back to the menu for another selection.
        (recur )
      )
    )
  )
)



;; ------------------------------
;; Run the program.
;; Calls the `menu` function to start the program, which begins displaying the menu and processing user input.
(menu)

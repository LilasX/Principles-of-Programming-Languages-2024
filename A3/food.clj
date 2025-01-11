(ns food
    ;; imports the clojure.string library, which contains useful functions for string manipulation (like trimming). The alias str is used to refer to this library.
    (:require [clojure.string :as str])
    ;; imports the clojure.string library again with a different alias, stringy, for potential alternate string functions or usage.
    (:require [clojure.string :as stringy])
    ;; imports the clojure.java.io library for file input/output operations. The alias io is used to access this library's functions.
    (:require [clojure.java.io :as io])
)

;; Check if the map is a valid map for Fido
(defn valid-map? [map-content]
  ;; Split map content into rows, remove extra whitespace from each row
  ;; Trim spaces from each row
  (let [rows (map str/trim (str/split map-content #"\n"))
        ;; Get lengths of each row
        row-lengths (map count rows)
        ;; Valid symbols check
        valid-symbols? (fn [row] (every? #(contains? #{\@ \- \#} %) row))
        ;; Count occurrences of '@'
        at-symbol-count (count (filter #(= \@ %) (apply str rows)))]

    ;; Debugging: print rows and lengths
    ;(println "Rows: " rows)
    ;(println "Row lengths: " row-lengths)

    ;; Check if all rows have the same length, all rows contain valid symbols,
    ;; and there is exactly one '@' in the entire map.
    (and 
      ;; Check if all rows have the same length
      (apply = row-lengths)
      ;; Check if all rows contain valid symbols
      (every? valid-symbols? rows)
      ;; Check if there is exactly one '@'
      (= 1 at-symbol-count)
    )
  )
)

;; Function to find the food in the map
;; Define the main function that takes the map as input
(defn find-food [map-data]
    ;; Convert the input map data (string) into a 2D vector (list of lists)
    ;; Split map into rows and convert each row into a vector
    (let [grid (vec (map vec (str/split map-data #"\n")))
        ;; Get the number of rows in the grid
        rows (count grid)
        ;; Get the number of columns by counting the first row
        cols (count (first grid))
        ;; Define the start position at the top-left corner (0, 0)
        start [0 0]
        ;; List of possible directions to move (right, down, left, up)
        directions [[0 1] [1 0] [0 -1] [-1 0]]]

        ;; Helper function to recursively search for the food
        ;; Define a search function with position, visited set, and the current grid as arguments
        (defn search [pos visited result-grid]
            ;; Destructure the current position into x (row) and y (column)
            (let [[x y] pos]
                ;; If out of bounds, already visited, or blocked by a wall (#), stop searching
                ;; Check if the position is out of bounds
                (if (or (< x 0) (>= x rows) (< y 0) (>= y cols)
                    ;; Check if the position has already been visited
                    (visited pos)
                    ;; Check if the position is blocked by a wall (#)
                    (= (get-in result-grid [x y]) \#))
                    ;; Return false, visited set, and the grid without changes if the conditions are met
                    [false visited result-grid]
                    ;; If food is found at this position
                    ;; Check if the current position contains food (@)
                    (if (= (get-in result-grid [x y]) \@)
                        ;; Return true, visited set, and the grid if food is found
                        [true visited result-grid]
                        ;; Otherwise, mark the position as visited and continue searching in the valid directions
                        ;; Add the current position to the visited set
                        (let [updated-visited (conj visited pos)]
                            ;; If it's a valid walkable path (-) or already marked as successful (+)
                            ;; Check if the current position is a walkable path (-)
                            (if (or (= (get-in result-grid [x y]) \-)
                                ;; Check if the position is already part of a successful path (+)
                                (= (get-in result-grid [x y]) \+))
                                ;; Loop through all directions and recursively search for the food
                                ;; Initialize a loop over the directions
                                (loop [dirs directions current-grid result-grid]
                                    ;; If no directions are left to check
                                    (if (empty? dirs)
                                        ;; Return false, updated visited set, and the current grid
                                        [false updated-visited current-grid]
                                        ;; Get the current direction (dx, dy)
                                        (let [[dx dy] (first dirs)
                                            ;; Recursively search in the new direction
                                            [found next-visited next-grid] (search [(+ x dx) (+ y dy)] updated-visited current-grid)]
                                            ;; If food is found in this direction
                                            (if found 
                                                ;; Mark the path as successful (+)
                                                [true next-visited (assoc-in next-grid [x y] \+)] 
                                                ;; If food is not found, mark the current path as ! (failed attempt)
                                                ;; Continue checking other directions
                                                (recur (rest dirs) (assoc-in next-grid [x y] \!))
                                            )
                                        )
                                    )
                                ) 
                                ;; If the current position is blocked or already visited, backtrack and mark !
                                ;; If the position is walkable or successful
                                (if (or (= (get-in result-grid [x y]) \-) (= (get-in result-grid [x y]) \+))
                                    ;; Mark the current position as ! (failed path) and backtrack
                                    [false updated-visited (assoc-in result-grid [x y] \!)] 
                                    ;; Otherwise, do not modify the grid
                                    [false updated-visited result-grid]
                                )
                            )
                        )
                    )
                )
            )
        )  
        
        ;; Start the search from the top-left corner
        ;; Call the search function starting at the top-left corner with an empty visited set
        (let [[found _ final-grid] (search start #{}, grid)] 
            ;; Return whether food was found and the final grid as a string
            [found (map #(apply str %) final-grid)]
        )
    )
)  

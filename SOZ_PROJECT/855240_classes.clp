; Sat Jan 23 13:35:24 EET 2016
; 
;+ (version "3.5")
;+ (build "Build 663")

(defclass %3ACLIPS_TOP_LEVEL_SLOT_CLASS "Fake class to save top-level slot information"
	(is-a USER)
	(role abstract)
	(single-slot is_driving
		(type SYMBOL)
		(allowed-values FALSE TRUE)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot drinkingSuggester_Class14
		(type STRING)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot alcohol_percentage
		(type INTEGER)
		(range 0 100)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot prefers_drink
		(type INSTANCE)
;+		(allowed-classes Alcoholic NonAlcoholic)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot people_number
		(type INTEGER)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot salty
		(type SYMBOL)
		(allowed-values FALSE TRUE)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot crush_is_there
		(type SYMBOL)
		(allowed-values FALSE TRUE)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot season
		(type SYMBOL)
		(allowed-values Summer Winter Spring Autumn)
;+		(cardinality 1 1)
		(create-accessor read-write))
	(single-slot Weight
		(type FLOAT)
		(range 0.0 2.0)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot light
		(type SYMBOL)
		(allowed-values FALSE TRUE)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot name_object
		(type STRING)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot type
		(type SYMBOL)
		(allowed-values BoyGirl FamilyGathering Christmas Halloween December8 Disco Chalga)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot age
		(type INTEGER)
		(range 0 123)
;+		(cardinality 1 1)
		(create-accessor read-write))
	(single-slot mood
		(type INTEGER)
		(range 0 100)
;+		(cardinality 1 1)
		(create-accessor read-write))
	(single-slot cold
		(type SYMBOL)
		(allowed-values FALSE TRUE)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot how_healty
		(type INTEGER)
		(range 0 100)
;+		(cardinality 1 1)
		(create-accessor read-write))
	(single-slot temperature
		(type FLOAT)
		(range -30.0 50.0)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(multislot prefers_food
		(type INSTANCE)
;+		(allowed-classes Meat Salad Snacks)
		(cardinality 0 3)
		(create-accessor read-write)))

(defclass Beverage
	(is-a USER)
	(role abstract)
	(single-slot cold
		(type SYMBOL)
		(allowed-values FALSE TRUE)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot how_healty
		(type INTEGER)
		(range 0 100)
;+		(cardinality 1 1)
		(create-accessor read-write))
	(single-slot name_object
		(type STRING)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot Weight
		(type FLOAT)
		(range 0.0 2.0)
;+		(cardinality 0 1)
		(create-accessor read-write)))

(defclass NonAlcoholic
	(is-a Beverage)
	(role concrete)
	(pattern-match reactive)
	(single-slot how_healty
		(type INTEGER)
		(range 10 100)
;+		(cardinality 1 1)
		(create-accessor read-write)))

(defclass Water
	(is-a NonAlcoholic)
	(role concrete)
	(pattern-match reactive))

(defclass Coffee
	(is-a NonAlcoholic)
	(role concrete)
	(pattern-match reactive))

(defclass Juice
	(is-a NonAlcoholic)
	(role concrete)
	(pattern-match reactive))

(defclass Alcoholic
	(is-a Beverage)
	(role concrete)
	(pattern-match reactive)
	(single-slot how_healty
		(type INTEGER)
		(range 0 50)
;+		(cardinality 1 1)
		(create-accessor read-write))
	(single-slot alcohol_percentage
		(type INTEGER)
		(range 0 100)
;+		(cardinality 0 1)
		(create-accessor read-write)))

(defclass Beer
	(is-a Alcoholic)
	(role concrete)
	(pattern-match reactive)
	(single-slot light
		(type SYMBOL)
		(allowed-values FALSE TRUE)
;+		(cardinality 0 1)
		(create-accessor read-write)))

(defclass Wine
	(is-a Alcoholic)
	(role concrete)
	(pattern-match reactive))

(defclass Cider
	(is-a Alcoholic)
	(role concrete)
	(pattern-match reactive))

(defclass Spirits
	(is-a Alcoholic)
	(role concrete)
	(pattern-match reactive))

(defclass Food
	(is-a USER)
	(role concrete)
	(pattern-match reactive)
	(single-slot salty
		(type SYMBOL)
		(allowed-values FALSE TRUE)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot how_healty
		(type INTEGER)
		(range 0 100)
;+		(cardinality 1 1)
		(create-accessor read-write))
	(single-slot name_object
		(type STRING)
;+		(cardinality 0 1)
		(create-accessor read-write)))

(defclass Salad
	(is-a Food)
	(role concrete)
	(pattern-match reactive))

(defclass Meat
	(is-a Food)
	(role concrete)
	(pattern-match reactive))

(defclass Snacks
	(is-a Food)
	(role concrete)
	(pattern-match reactive))

(defclass Season
	(is-a USER)
	(role concrete)
	(pattern-match reactive)
	(single-slot season
		(type SYMBOL)
		(allowed-values Summer Winter Spring Autumn)
;+		(cardinality 1 1)
		(create-accessor read-write))
	(single-slot temperature
		(type FLOAT)
		(range -30.0 50.0)
;+		(cardinality 0 1)
		(create-accessor read-write)))

(defclass Person
	(is-a USER)
	(role concrete)
	(pattern-match reactive)
	(single-slot mood
		(type INTEGER)
		(range 0 100)
;+		(cardinality 1 1)
		(create-accessor read-write))
	(single-slot how_healty
		(type INTEGER)
		(range 0 100)
;+		(cardinality 1 1)
		(create-accessor read-write))
	(single-slot name_object
		(type STRING)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(multislot prefers_food
		(type INSTANCE)
;+		(allowed-classes Meat Salad Snacks)
		(cardinality 0 3)
		(create-accessor read-write))
	(single-slot prefers_drink
		(type INSTANCE)
;+		(allowed-classes Alcoholic NonAlcoholic)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot is_driving
		(type SYMBOL)
		(allowed-values FALSE TRUE)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot age
		(type INTEGER)
		(range 0 123)
;+		(cardinality 1 1)
		(create-accessor read-write)))

(defclass Party
	(is-a USER)
	(role concrete)
	(pattern-match reactive)
	(single-slot crush_is_there
		(type SYMBOL)
		(allowed-values FALSE TRUE)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot people_number
		(type INTEGER)
;+		(cardinality 0 1)
		(create-accessor read-write))
	(single-slot type
		(type SYMBOL)
		(allowed-values BoyGirl FamilyGathering Christmas Halloween December8 Disco Chalga)
;+		(cardinality 0 1)
		(create-accessor read-write)))
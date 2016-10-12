(deffunction test_healty_age (?age ?person_h ?beverage_h)
	(
		if(> ?beverage_h 80) then FALSE
		else (
			if(< (* (/ (- 100 ?age) 100) (/ ?person_h 100) (/ ?beverage_h 100)) (/ 1 7)) 
			then 
				FALSE
			else
				TRUE
			)
	)
)
(assert (continue true))

(deffunction fback ()
	(bind ?flag TRUE)
	(do-for-all-facts ((?index result))
		(bind ?flag FALSE)
	)
	(if (eq ?flag TRUE) then FALSE else TRUE)
)

(deftemplate posible 
	(slot person_name) 
	(slot beverage_name) 
	(slot season)
)

(defrule generate (declare (salience 10000))
	(object (is-a Person) (name_object ?person_name))
	(object (is-a Alcoholic|NonAlcoholic) (name_object ?beverage_name))
	(object (is-a Season) (season ?s))
=>
	(assert (posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s)))
)

(assert (names))
(defrule find_names
	?i <- (names $?n)
	(object (is-a Person) (name_object ?person_name))
	(test (not (member$ ?person_name $?n)))
=>
	(assert (names $?n ?person_name))
	(retract ?i)
)

(defrule retract_by_season1 (declare (salience 9000))
	?i <- (posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s))
	(object (is-a Beer) (name_object ?beverage_name))
	(object (is-a Season) (season ?s))
	(test (eq ?s Winter))
=>
	(retract ?i)
)

(defrule retract_by_season2 (declare (salience 9000)) 
	?i <- (posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s))
	(object (is-a Spirits) (name_object ?beverage_name))
	(object (is-a Season) (season ?s))
	(test (eq ?s Summer))
=>
	(retract ?i)
)

(defrule retract_by_driving (declare (salience 9000)) 
	?i <- (posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s))
	(object (is-a Person) (name_object ?person_name) (is_driving ?id))
	(object (is-a Alcoholic) (name_object ?beverage_name))
	(test (eq ?id TRUE))
=>
	(retract ?i)
)

(defrule retract_by_mood_Alcohol (declare (salience 9000))
	?i <- (posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s))
	(object (is-a Person) (name_object ?person_name) (mood ?md))
	(object (is-a Cider|Spirits|Wine|Coffee) (name_object ?beverage_name))
	(test (or (> ?md 95) (and (> ?md 20) (< ?md 40))))
=>
	(retract ?i)
)

(defrule retract_by_health (declare (salience 9000))
	?i <- (posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s))
	(object (is-a Person) (name_object ?person_name) (how_healty ?ph) (age ?a))
	(object (is-a NonAlcoholic|Alcoholic) (name_object ?beverage_name) (how_healty ?bh))
	(test (test_healty_age ?a ?ph ?bh))
=>
	(retract ?i)
)

(defrule it_is_a_date (declare (salience 9000))
	?i <- (posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s))
	(object (is-a NonAlcoholic|Cider|Beer|Spirits) (name_object ?beverage_name))
	(object (is-a Party) (crush_is_there ?cis) (people_number ?pn))
	(test (eq ?pn 2))
=>
	(retract ?i)
)

(defrule party_preferences1 (declare (salience 9000))
	?i <- (posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s))
	(object (is-a Coffee) (name_object ?beverage_name))
	(object (is-a Party) (type ?t&BoyGirl|December8|Disco|Chalga))
=>
	(retract ?i)
)

(defrule party_preferences2 (declare (salience 9000))
	?i <- (posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s))
	(object (is-a Spirits) (name_object ?beverage_name))
	(object (is-a Party) (type ?t&FamilyGathering|Christmas))
=>
	(retract ?i)
)

(defrule ask_for_time (declare (salience 8000))
	=>
		(printout t "Is it Summer or Winter ? " crlf)
		(assert (season (read)))
)

(defrule retract_by_input (declare (salience 7000)) 
	?i <- (posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s))
	(season ?ss)
	(test (not (eq ?ss ?s)))
=>
	(retract ?i)
)

(defmessage-handler Food print primary ()
	(printout t "name: " ?self:name_object " salty: " ?self:salty " how_healty: " ?self:how_healty crlf)
)

(defrule print_food (declare (salience 7001)) 
	?i <- (object (is-a Food))
=>
	(send ?i print)
)
	
	
(defrule ask_for_food (declare (salience 7000)) 
	=> 
		(printout t "Choose what food you prefer Salad, Meat, Snacks, None :" crlf)
		(assert (food (read)))
)

(deftemplate result
	(slot person_name) 
	(slot beverage_name) 
	(slot food_name)
)

(defrule generate_food (declare (salience 6000)) 
	(posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s))
	(food ?f&Salad|Meat|Snacks)
	(object (is-a ?f&Meat|Salad|Snacks) (name_object ?food_name))
=>
	(assert (result (person_name ?person_name) (food_name ?food_name) (beverage_name ?beverage_name)))
)

(defrule is_generated_food (declare (salience 5500)) 
	?i <- (posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s))
=>
	(retract ?i)
)

(defrule is_not_generated_food (declare (salience 5000)) 
	?i <- (posible (person_name ?person_name) (beverage_name ?beverage_name) (season ?s))
=>
	(assert (final ?person_name ?beverage_name))
	(retract ?i)
)

(defrule fall_back (declare (salience 4909))
	?i <- (continue true)
	(test (fback))
=>
	(retract ?i)
	(assert (continue false))
)

(defrule likes_food (declare (salience 4900))
	(continue true)
	(result (person_name ?person_name) (food_name ?food_name) (beverage_name ?beverage_name))
	(object (is-a Person) (name_object ?person_name) (prefers_food $?pf))
	(test (member$ ?food_name $?pf))
=>
	(assert (result (person_name ?person_name) (food_name ?food_name) (beverage_name ?beverage_name)))	
)

(defrule retract_by_Coffee_and_Salad (declare (salience 4000))
	(continue true)
	?i <- (result (person_name ?person_name) (food_name ?food_name) (beverage_name ?beverage_name))
	(object (is-a Salad|Meat) (name_object ?food_name))
	(object (is-a Coffee) (name_object ?beverage_name))
=>
	(retract ?i)
)

(defrule retract_by_wine (declare (salience 4000)) 
	(continue true)
	?i <- (result (person_name ?person_name) (food_name ?food_name) (beverage_name ?beverage_name))
	(object (is-a Snacks) (name_object ?food_name))
	(object (is-a Wine) (name_object ?beverage_name))
=>
	(retract ?i)
)

(defrule retract_by_food (declare (salience 4000)) 
	(continue true)
	?i <- (result (person_name ?person_name) (food_name ?food_name) (beverage_name ?beverage_name))
	(object (is-a Food) (name_object ?food_name) (salty ?salt) (how_healty ?food_h))
	(object (is-a NonAlcoholic|Alcoholic) 
	(name_object ?beverage_name) (how_healty ?beverage_h) (cold ?c))
	(test (or (and (eq ?salt FALSE) (eq ?c FALSE)) (< ?beverage_h (+ ?food_h 10))))
=>
	(retract ?i)
)

(defrule retract_by_weight_1 (declare (salience 4000))
	(continue true)
	?i <- (result (person_name ?person_name) (food_name ?food_name) (beverage_name ?beverage_name))
	(object (is-a Salad) (name_object ?food_name) (salty ?salt) (how_healty ?food_h))
	(object (is-a NonAlcoholic|Alcoholic) (name_object ?beverage_name) (Weight ?w))
	(test (> ?w 0.2))
=>
	(retract ?i)
)

(defrule retract_by_weight_2 (declare (salience 4000))
	(continue true)
	?i <- (result (person_name ?person_name) (food_name ?food_name) (beverage_name ?beverage_name))
	(object (is-a Meat) (name_object ?food_name) (salty ?salt) (how_healty ?food_h))
	(object (is-a NonAlcoholic|Alcoholic) (name_object ?beverage_name) (Weight ?w))
	(test (< ?w 0.19))
=>
	(retract ?i)
)

(defglobal ?*checked* = (create$))
(defrule end (declare (salience -10000))
	(continue true)
	(names $?everybody)
=>
	(bind ?len (length $?everybody))
	(while (> ?len 0) do
		(bind ?*checked* (create$ ))
		(bind ?nothing TRUE)
		(printout t crlf (nth$ ?len $?everybody) " can have : " crlf)
		(do-for-all-facts ((?r1 result))
			(if (and (eq ?r1:person_name (nth$ ?len $?everybody)) (not (member$ ?r1:beverage_name ?*checked*))) 
			then 
				(printout t ?r1:beverage_name " with some ")
				(do-for-all-facts ((?r2 result))
					(if (and (eq ?r2:beverage_name ?r1:beverage_name) (eq ?r2:person_name ?r1:person_name) )
					then 
						(printout t ?r2:food_name " ,")
					)
				)
				(printout t crlf)
				(bind ?*checked* (insert$ ?*checked* 1 ?r1:beverage_name))
			)
			(bind ?nothing FALSE)
		)
		(if (eq ?nothing TRUE) then (printout t "Water or some Juice" crlf))
		(bind ?len (- ?len 1))
	)
)

































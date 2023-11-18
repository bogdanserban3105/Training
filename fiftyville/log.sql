-- Keep a log of any SQL queries you execute as you solve the mystery.
--SELECT street FROM crime_scene_reports WHERE (month = 7 and day = 28);
--SELECT description FROM crime_scene_reports WHERE (street = "Axmark Road" AND month = 7 and day = 28);
--SELECT description FROM crime_scene_reports WHERE (street = "Boyce Avenue" AND month = 7 and day = 28);
--SELECT id FROM crime_scene_reports WHERE (street = "Humphrey Street" AND month = 7 and day = 28);                 ID:295 si 297
--SELECT description FROM crime_scene_reports WHERE (street = "Widenius Street" AND month = 7 and day = 28);
--SELECT description FROM crime_scene_reports WHERE (street = "Humphrey Street" AND month = 7 and day = 28); --au scapat pe Humphrey Street
--SELECT * from interviews JOIN crime_scene_reports ON interviews.id = crime_scene_reports.id WHERE(SELECT crime_scene_reports.id FROM crime_scene_reports WHERE (street = "Humphrey Street" AND month = 7 and day = 28))

--Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left
--| I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some
--As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The
--SELECT transcript from interviews JOIN crime_scene_reports ON interviews.id = crime_scene_reports.id WHERE( SELECT crime_scene_reports.id FROM crime_scene_reports WHERE (street = "Humphrey Street" AND month = 7 and day = 28 and name = "David"))

-- Ezekiah Hopkins???
-- Miss Sutherland ??? Mr Windibank ??? Mr hardy ?? Hosmer Angel???
-- Miss Sutherland again Mr Windibank again Mr hardy again  Hosmer Angel again
-- a place Briony Lodge, Pope's Court
-- Mr holmes
-- Spaulding-  SEARCH FOR ARCHIE

--SELECT * from interviews JOIN crime_scene_reports ON interviews.id = crime_scene_reports.id WHERE( SELECT crime_scene_reports.id FROM crime_scene_reports WHERE (street = "Humphrey Street" AND month = 7 and day = 28 and crime_scene_reports.id = 295 ))
--SELECT * FROM bakery_security_logs WHERE (month = 7 and day = 28 and hour = 10 )

--SELECT name FROM people WHERE license_plate = "13FNH73" -- SOPHIA posibilitate scazuta
--SELECT name FROM people WHERE license_plate = "5P2BI95" -- VANESSA la 10:16
--SELECT name FROM people WHERE license_plate = "94KL13X" -- Bruce la 10:18

--SELECT phone_number FROM people WHERE license_plate = "13FNH73"; -- SOPHIA posibilitate scazuta; (027) 555-1068
--SELECT phone_number FROM people WHERE license_plate = "5P2BI95"; -- VANESSA la 10:16; (725) 555-4692
--SELECT phone_number FROM people WHERE license_plate = "94KL13X"; -- Bruce la 10:18 (367) 555-5533
--SELECT * FROM phone_calls WHERE caller = "(027) 555-1068"; - EXCLUDe SOPHIA///XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX X
--SELECT * FROM phone_calls WHERE caller = "(725) 555-4692"; -- (821) 555-5262 Amanda EXCLUDe SOPHIA///XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX X
--SELECT * FROM phone_calls WHERE caller = "(367) 555-5533"; -- -(375) 555-8161- Robin    -(344) 555-9601-  Deborah   -(022) 555-4052- Gregory (704) 555-5790 Carl

--| id  |     caller     |    receiver    | year | month | day | duration |
--| 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |  Robin
--| 236 | (367) 555-5533 | (344) 555-9601 | 2021 | 7     | 28  | 120      | Deborah
--| 245 | (367) 555-5533 | (022) 555-4052 | 2021 | 7     | 28  | 241      | Gregory
--| 285 | (367) 555-5533 | (704) 555-5790 | 2021 | 7     | 28  | 75       | Carl

--SELECT * FROM people WHERE phone_number = "(704) 555-5790";
--Select name from bank_accounts join people ON people.id = bank_accounts.person_id Join atm_transactions On bank_accounts.account_number = atm_transactions.account_number WHERE (day = 28 and month = 7 and transaction_type != 'deposit')
--  Bruce     | bruce is the suspect


--SELECT passport_number From people where name = "Bruce"; 5773159633

--Select flight_id from passengers where passport_number = 5773159633; 36

--select * from flights where id = 36
--id | origin_airport_id | destination_airport_id | year | month | day | hour | minute
--36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20

-- Select * from airports
-- Bruce a plecat la 8 20 pe data de 28 a 7 a din Fiftyville la NY  BRUCE suspect

--| id | abbreviation |                full_name                |     city      |
--| 4  | LGA          | LaGuardia Airport                       | New York City |

--SELECT * FROM people WHERE license_plate = "4V16VO0";

--SELECT name FROM people WHERE license_plate = "4V16VO0" ROBIN
--Select * from bank_accounts join people ON people.id = bank_accounts.person_id Join atm_transactions On bank_accounts.account_number = atm_transactions.account_number WHERE (people.name = 'Bruce');
--Select * from bank_accounts join people ON people.id = bank_accounts.person_id Join atm_transactions On bank_accounts.account_number = atm_transactions.account_number WHERE (people.id = 864400)
--  account_number | person_id | creation_year |   id   | name  |  phone_number  | passport_number | license_plate |  id  | account_number | year | month | day |     atm_location     | transaction_type | amount
--| 94751264       | 864400    | 2019          | 864400 | Robin | (375) 555-8161 |                 | 4V16VO0       | 652  | 94751264       | 2021 | 7     | 30  | Leggett Street       | withdraw         | 10     |

--Robin been to Laggett Streeet Atm, so he;s the accomplice
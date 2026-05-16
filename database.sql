-- ============================================
-- База данных: Автомастерские
-- Вариант 10
-- ============================================

DROP TABLE IF EXISTS master_stats;
DROP TABLE IF EXISTS repairs;
DROP TABLE IF EXISTS masters;
DROP TABLE IF EXISTS cars;
DROP TABLE IF EXISTS workshops;
DROP TABLE IF EXISTS users;

-- Таблица пользователей
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    login TEXT NOT NULL UNIQUE,
    password TEXT NOT NULL,
    role TEXT NOT NULL CHECK(role IN ('manager', 'master')),
    full_name TEXT NOT NULL
);

-- Таблица мастерских
CREATE TABLE workshops (
    number INTEGER PRIMARY KEY,
    address TEXT NOT NULL,
    car_brands TEXT NOT NULL
);

-- Таблица автомобилей
CREATE TABLE cars (
    license_plate TEXT PRIMARY KEY,
    brand TEXT NOT NULL,
    year INTEGER,
    owner_name TEXT NOT NULL,
    tech_passport TEXT NOT NULL,
    owner_address TEXT
);

-- Таблица мастеров
CREATE TABLE masters (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    position TEXT,
    workshop_number INTEGER,
    FOREIGN KEY (workshop_number) REFERENCES workshops(number) ON DELETE SET NULL
);

-- Таблица выполненных работ
CREATE TABLE repairs (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    workshop_number INTEGER NOT NULL,
    start_date TEXT NOT NULL,
    end_date TEXT NOT NULL,
    license_plate TEXT NOT NULL,
    repair_type TEXT NOT NULL,
    cost REAL NOT NULL,
    master_name TEXT NOT NULL,
    FOREIGN KEY (workshop_number) REFERENCES workshops(number) ON DELETE CASCADE,
    FOREIGN KEY (license_plate) REFERENCES cars(license_plate) ON DELETE CASCADE
);

-- Таблица статистики мастеров
CREATE TABLE master_stats (
    master_id INTEGER NOT NULL,
    repair_type TEXT NOT NULL,
    repairs_count INTEGER DEFAULT 0,
    PRIMARY KEY (master_id, repair_type),
    FOREIGN KEY (master_id) REFERENCES masters(id) ON DELETE CASCADE
);

-- Тестовые данные
INSERT INTO users (login, password, role, full_name) VALUES 
('manager1', '123', 'manager', 'Иванов Иван Менеджер'),
('master1', '123', 'master', 'Петров Петр Мастер'),
('master2', '123', 'master', 'Сидорова Анна Мастер');

INSERT INTO workshops (number, address, car_brands) VALUES 
(1, 'ул. Ленина, 1, г. Минск', 'Toyota, BMW, Mercedes, Audi'),
(2, 'ул. Гагарина, 5, г. Минск', 'Honda, Nissan, Kia, Hyundai'),
(3, 'пр. Независимости, 10, г. Минск', 'Volkswagen, Skoda, Ford');

INSERT INTO cars (license_plate, brand, year, owner_name, tech_passport, owner_address) VALUES 
('A123BC', 'Toyota', 2020, 'Сидоров Сидор', 'TP123456', 'ул. Пушкина, 10, Минск'),
('B456CD', 'BMW', 2019, 'Кузнецов Кузьма', 'TP789012', 'ул. Лермонтова, 20, Минск'),
('C789DE', 'Honda', 2021, 'Васильев Василий', 'TP345678', 'ул. Горького, 30, Минск'),
('D012EF', 'Volkswagen', 2018, 'Михайлов Михаил', 'TP901234', 'ул. Чехова, 40, Минск'),
('E345FG', 'Mercedes', 2022, 'Алексеев Алексей', 'TP567890', 'ул. Толстого, 50, Минск');

INSERT INTO masters (name, position, workshop_number) VALUES 
('Петров Петр Мастер', 'Слесарь-ремонтник', 1),
('Сидорова Анна Мастер', 'Автоэлектрик', 1),
('Козлов Дмитрий', 'Механик', 2),
('Морозова Елена', 'Диагност', 2),
('Волков Сергей', 'Мастер кузовного ремонта', 3);

INSERT INTO repairs (workshop_number, start_date, end_date, license_plate, repair_type, cost, master_name) VALUES 
(1, '2024-01-10', '2024-01-12', 'A123BC', 'Замена поршневой', 500.00, 'Петров Петр Мастер'),
(1, '2024-01-15', '2024-01-16', 'B456CD', 'Регулировка клапанов', 300.00, 'Петров Петр Мастер'),
(1, '2024-01-20', '2024-01-21', 'E345FG', 'Замена масла', 150.00, 'Сидорова Анна Мастер'),
(2, '2024-02-01', '2024-02-05', 'C789DE', 'Замена ведущих шестерен', 800.00, 'Козлов Дмитрий'),
(2, '2024-02-10', '2024-02-11', 'C789DE', 'Замена масла', 150.00, 'Морозова Елена'),
(3, '2024-02-15', '2024-02-20', 'D012EF', 'Покраска кузова', 1200.00, 'Волков Сергей');

INSERT INTO master_stats (master_id, repair_type, repairs_count) VALUES 
(1, 'Замена поршневой', 1),
(1, 'Регулировка клапанов', 1),
(2, 'Замена масла', 1),
(3, 'Замена ведущих шестерен', 1),
(4, 'Замена масла', 1),
(5, 'Покраска кузова', 1);


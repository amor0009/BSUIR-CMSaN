--
-- PostgreSQL database dump
--

-- Dumped from database version 16.3
-- Dumped by pg_dump version 16.3

-- Started on 2025-03-06 04:03:56

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET xmloption = content;
SET client_min_messages = warning;
SET row_security = off;

--
-- TOC entry 4 (class 2615 OID 2200)
-- Name: public; Type: SCHEMA; Schema: -; Owner: pg_database_owner
--

CREATE SCHEMA public;


ALTER SCHEMA public OWNER TO pg_database_owner;

--
-- TOC entry 4907 (class 0 OID 0)
-- Dependencies: 4
-- Name: SCHEMA public; Type: COMMENT; Schema: -; Owner: pg_database_owner
--

COMMENT ON SCHEMA public IS 'standard public schema';


SET default_tablespace = '';

SET default_table_access_method = heap;

--
-- TOC entry 223 (class 1259 OID 27152)
-- Name: Водители; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Водители" (
    "id водителя" integer NOT NULL,
    "ФИО" character varying(60) NOT NULL,
    "Возраст" integer NOT NULL,
    "Стаж вождения" integer NOT NULL,
    "Номер водительского удостоверени" character varying(30) NOT NULL,
    "id транспортной операции" integer NOT NULL
);


ALTER TABLE public."Водители" OWNER TO postgres;

--
-- TOC entry 221 (class 1259 OID 27150)
-- Name: Водители_id водителя_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Водители_id водителя_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Водители_id водителя_seq" OWNER TO postgres;

--
-- TOC entry 4908 (class 0 OID 0)
-- Dependencies: 221
-- Name: Водители_id водителя_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Водители_id водителя_seq" OWNED BY public."Водители"."id водителя";


--
-- TOC entry 222 (class 1259 OID 27151)
-- Name: Водители_id транспортной операци_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Водители_id транспортной операци_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Водители_id транспортной операци_seq" OWNER TO postgres;

--
-- TOC entry 4909 (class 0 OID 0)
-- Dependencies: 222
-- Name: Водители_id транспортной операци_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Водители_id транспортной операци_seq" OWNED BY public."Водители"."id транспортной операции";


--
-- TOC entry 231 (class 1259 OID 27177)
-- Name: Грузы; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Грузы" (
    "id груза" integer NOT NULL,
    "Название" character varying(100) NOT NULL,
    "Вес" double precision NOT NULL,
    "Объём" double precision,
    "Дата погрузки" date,
    "id транспортной операции" integer NOT NULL
);


ALTER TABLE public."Грузы" OWNER TO postgres;

--
-- TOC entry 238 (class 1259 OID 27196)
-- Name: Грузы-Транспортные средства; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Грузы-Транспортные средства" (
    id integer NOT NULL,
    "id груза" integer NOT NULL,
    "id транспортного средства" integer NOT NULL
);


ALTER TABLE public."Грузы-Транспортные средства" OWNER TO postgres;

--
-- TOC entry 237 (class 1259 OID 27195)
-- Name: Грузы-Транспорт_id транспортного_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Грузы-Транспорт_id транспортного_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Грузы-Транспорт_id транспортного_seq" OWNER TO postgres;

--
-- TOC entry 4910 (class 0 OID 0)
-- Dependencies: 237
-- Name: Грузы-Транспорт_id транспортного_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Грузы-Транспорт_id транспортного_seq" OWNED BY public."Грузы-Транспортные средства"."id транспортного средства";


--
-- TOC entry 236 (class 1259 OID 27194)
-- Name: Грузы-Транспортные сред_id груза_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Грузы-Транспортные сред_id груза_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Грузы-Транспортные сред_id груза_seq" OWNER TO postgres;

--
-- TOC entry 4911 (class 0 OID 0)
-- Dependencies: 236
-- Name: Грузы-Транспортные сред_id груза_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Грузы-Транспортные сред_id груза_seq" OWNED BY public."Грузы-Транспортные средства"."id груза";


--
-- TOC entry 235 (class 1259 OID 27193)
-- Name: Грузы-Транспортные средства_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Грузы-Транспортные средства_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Грузы-Транспортные средства_id_seq" OWNER TO postgres;

--
-- TOC entry 4912 (class 0 OID 0)
-- Dependencies: 235
-- Name: Грузы-Транспортные средства_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Грузы-Транспортные средства_id_seq" OWNED BY public."Грузы-Транспортные средства".id;


--
-- TOC entry 229 (class 1259 OID 27175)
-- Name: Грузы_id груза_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Грузы_id груза_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Грузы_id груза_seq" OWNER TO postgres;

--
-- TOC entry 4913 (class 0 OID 0)
-- Dependencies: 229
-- Name: Грузы_id груза_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Грузы_id груза_seq" OWNED BY public."Грузы"."id груза";


--
-- TOC entry 230 (class 1259 OID 27176)
-- Name: Грузы_id транспортной операции_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Грузы_id транспортной операции_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Грузы_id транспортной операции_seq" OWNER TO postgres;

--
-- TOC entry 4914 (class 0 OID 0)
-- Dependencies: 230
-- Name: Грузы_id транспортной операции_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Грузы_id транспортной операции_seq" OWNED BY public."Грузы"."id транспортной операции";


--
-- TOC entry 216 (class 1259 OID 27133)
-- Name: Клиенты; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Клиенты" (
    "id клиента" integer NOT NULL,
    "Название организации" character varying(100) NOT NULL,
    "Адрес" character varying(100) NOT NULL,
    "Номер телефона" character varying(20) NOT NULL,
    "Адрес электронной почты" character varying(50) NOT NULL
);


ALTER TABLE public."Клиенты" OWNER TO postgres;

--
-- TOC entry 242 (class 1259 OID 27207)
-- Name: Клиенты-Транспортные операции; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Клиенты-Транспортные операции" (
    id integer NOT NULL,
    "id клиента" integer NOT NULL,
    "id транспортной операции" integer NOT NULL
);


ALTER TABLE public."Клиенты-Транспортные операции" OWNER TO postgres;

--
-- TOC entry 241 (class 1259 OID 27206)
-- Name: Клиенты-Транспо_id транспортной _seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Клиенты-Транспо_id транспортной _seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Клиенты-Транспо_id транспортной _seq" OWNER TO postgres;

--
-- TOC entry 4915 (class 0 OID 0)
-- Dependencies: 241
-- Name: Клиенты-Транспо_id транспортной _seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Клиенты-Транспо_id транспортной _seq" OWNED BY public."Клиенты-Транспортные операции"."id транспортной операции";


--
-- TOC entry 240 (class 1259 OID 27205)
-- Name: Клиенты-Транспортные _id клиента_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Клиенты-Транспортные _id клиента_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Клиенты-Транспортные _id клиента_seq" OWNER TO postgres;

--
-- TOC entry 4916 (class 0 OID 0)
-- Dependencies: 240
-- Name: Клиенты-Транспортные _id клиента_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Клиенты-Транспортные _id клиента_seq" OWNED BY public."Клиенты-Транспортные операции"."id клиента";


--
-- TOC entry 239 (class 1259 OID 27204)
-- Name: Клиенты-Транспортные операции_id_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Клиенты-Транспортные операции_id_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Клиенты-Транспортные операции_id_seq" OWNER TO postgres;

--
-- TOC entry 4917 (class 0 OID 0)
-- Dependencies: 239
-- Name: Клиенты-Транспортные операции_id_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Клиенты-Транспортные операции_id_seq" OWNED BY public."Клиенты-Транспортные операции".id;


--
-- TOC entry 215 (class 1259 OID 27132)
-- Name: Клиенты_id клиента_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Клиенты_id клиента_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Клиенты_id клиента_seq" OWNER TO postgres;

--
-- TOC entry 4918 (class 0 OID 0)
-- Dependencies: 215
-- Name: Клиенты_id клиента_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Клиенты_id клиента_seq" OWNED BY public."Клиенты"."id клиента";


--
-- TOC entry 225 (class 1259 OID 27160)
-- Name: Маршруты; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Маршруты" (
    "id маршрута" integer NOT NULL,
    "Точка отправления" character varying(20) NOT NULL,
    "Точка прибытия" character varying(20) NOT NULL,
    "Расстояние" double precision NOT NULL,
    "Время в пути" time without time zone NOT NULL
);


ALTER TABLE public."Маршруты" OWNER TO postgres;

--
-- TOC entry 224 (class 1259 OID 27159)
-- Name: Маршруты_id маршрута_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Маршруты_id маршрута_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Маршруты_id маршрута_seq" OWNER TO postgres;

--
-- TOC entry 4919 (class 0 OID 0)
-- Dependencies: 224
-- Name: Маршруты_id маршрута_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Маршруты_id маршрута_seq" OWNED BY public."Маршруты"."id маршрута";


--
-- TOC entry 220 (class 1259 OID 27142)
-- Name: Оплаты; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Оплаты" (
    "id оплаты" integer NOT NULL,
    "Сумма" double precision,
    "Дата оплаты" date,
    "Способ оплаты" character varying(20),
    "id клиента" integer NOT NULL,
    "id транспортной операции" integer NOT NULL
);


ALTER TABLE public."Оплаты" OWNER TO postgres;

--
-- TOC entry 218 (class 1259 OID 27140)
-- Name: Оплаты_id клиента_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Оплаты_id клиента_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Оплаты_id клиента_seq" OWNER TO postgres;

--
-- TOC entry 4920 (class 0 OID 0)
-- Dependencies: 218
-- Name: Оплаты_id клиента_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Оплаты_id клиента_seq" OWNED BY public."Оплаты"."id клиента";


--
-- TOC entry 217 (class 1259 OID 27139)
-- Name: Оплаты_id оплаты_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Оплаты_id оплаты_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Оплаты_id оплаты_seq" OWNER TO postgres;

--
-- TOC entry 4921 (class 0 OID 0)
-- Dependencies: 217
-- Name: Оплаты_id оплаты_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Оплаты_id оплаты_seq" OWNED BY public."Оплаты"."id оплаты";


--
-- TOC entry 219 (class 1259 OID 27141)
-- Name: Оплаты_id транспортной операции_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Оплаты_id транспортной операции_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Оплаты_id транспортной операции_seq" OWNER TO postgres;

--
-- TOC entry 4922 (class 0 OID 0)
-- Dependencies: 219
-- Name: Оплаты_id транспортной операции_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Оплаты_id транспортной операции_seq" OWNED BY public."Оплаты"."id транспортной операции";


--
-- TOC entry 234 (class 1259 OID 27186)
-- Name: Транспортные операции; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Транспортные операции" (
    "id транспортной операции" integer NOT NULL,
    "Статус" character varying(15) NOT NULL,
    "Ожидаемое время доставки" time without time zone,
    "Дата прибытия" date,
    "id маршрута" integer NOT NULL
);


ALTER TABLE public."Транспортные операции" OWNER TO postgres;

--
-- TOC entry 232 (class 1259 OID 27184)
-- Name: Транспортные оп_id транспортной _seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Транспортные оп_id транспортной _seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Транспортные оп_id транспортной _seq" OWNER TO postgres;

--
-- TOC entry 4923 (class 0 OID 0)
-- Dependencies: 232
-- Name: Транспортные оп_id транспортной _seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Транспортные оп_id транспортной _seq" OWNED BY public."Транспортные операции"."id транспортной операции";


--
-- TOC entry 233 (class 1259 OID 27185)
-- Name: Транспортные операци_id маршрута_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Транспортные операци_id маршрута_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Транспортные операци_id маршрута_seq" OWNER TO postgres;

--
-- TOC entry 4924 (class 0 OID 0)
-- Dependencies: 233
-- Name: Транспортные операци_id маршрута_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Транспортные операци_id маршрута_seq" OWNED BY public."Транспортные операции"."id маршрута";


--
-- TOC entry 228 (class 1259 OID 27168)
-- Name: Транспортные средства; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public."Транспортные средства" (
    "id транспортного средства" integer NOT NULL,
    "Производитель" character varying(20) NOT NULL,
    "Модель" character varying(20) NOT NULL,
    "Грузоподъёмность" double precision NOT NULL,
    "Регистрационный номер" character varying(10) NOT NULL,
    "id транспортной операции" integer NOT NULL
);


ALTER TABLE public."Транспортные средства" OWNER TO postgres;

--
-- TOC entry 226 (class 1259 OID 27166)
-- Name: Транспортные ср_id транспортного_seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Транспортные ср_id транспортного_seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Транспортные ср_id транспортного_seq" OWNER TO postgres;

--
-- TOC entry 4925 (class 0 OID 0)
-- Dependencies: 226
-- Name: Транспортные ср_id транспортного_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Транспортные ср_id транспортного_seq" OWNED BY public."Транспортные средства"."id транспортного средства";


--
-- TOC entry 227 (class 1259 OID 27167)
-- Name: Транспортные ср_id транспортной _seq; Type: SEQUENCE; Schema: public; Owner: postgres
--

CREATE SEQUENCE public."Транспортные ср_id транспортной _seq"
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;


ALTER SEQUENCE public."Транспортные ср_id транспортной _seq" OWNER TO postgres;

--
-- TOC entry 4926 (class 0 OID 0)
-- Dependencies: 227
-- Name: Транспортные ср_id транспортной _seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: postgres
--

ALTER SEQUENCE public."Транспортные ср_id транспортной _seq" OWNED BY public."Транспортные средства"."id транспортной операции";


--
-- TOC entry 4688 (class 2604 OID 27155)
-- Name: Водители id водителя; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Водители" ALTER COLUMN "id водителя" SET DEFAULT nextval('public."Водители_id водителя_seq"'::regclass);


--
-- TOC entry 4689 (class 2604 OID 27156)
-- Name: Водители id транспортной операции; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Водители" ALTER COLUMN "id транспортной операции" SET DEFAULT nextval('public."Водители_id транспортной операци_seq"'::regclass);


--
-- TOC entry 4693 (class 2604 OID 27180)
-- Name: Грузы id груза; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Грузы" ALTER COLUMN "id груза" SET DEFAULT nextval('public."Грузы_id груза_seq"'::regclass);


--
-- TOC entry 4694 (class 2604 OID 27181)
-- Name: Грузы id транспортной операции; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Грузы" ALTER COLUMN "id транспортной операции" SET DEFAULT nextval('public."Грузы_id транспортной операции_seq"'::regclass);


--
-- TOC entry 4697 (class 2604 OID 27199)
-- Name: Грузы-Транспортные средства id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Грузы-Транспортные средства" ALTER COLUMN id SET DEFAULT nextval('public."Грузы-Транспортные средства_id_seq"'::regclass);


--
-- TOC entry 4698 (class 2604 OID 27200)
-- Name: Грузы-Транспортные средства id груза; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Грузы-Транспортные средства" ALTER COLUMN "id груза" SET DEFAULT nextval('public."Грузы-Транспортные сред_id груза_seq"'::regclass);


--
-- TOC entry 4699 (class 2604 OID 27201)
-- Name: Грузы-Транспортные средства id транспортного средства; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Грузы-Транспортные средства" ALTER COLUMN "id транспортного средства" SET DEFAULT nextval('public."Грузы-Транспорт_id транспортного_seq"'::regclass);


--
-- TOC entry 4684 (class 2604 OID 27136)
-- Name: Клиенты id клиента; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Клиенты" ALTER COLUMN "id клиента" SET DEFAULT nextval('public."Клиенты_id клиента_seq"'::regclass);


--
-- TOC entry 4700 (class 2604 OID 27210)
-- Name: Клиенты-Транспортные операции id; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Клиенты-Транспортные операции" ALTER COLUMN id SET DEFAULT nextval('public."Клиенты-Транспортные операции_id_seq"'::regclass);


--
-- TOC entry 4701 (class 2604 OID 27211)
-- Name: Клиенты-Транспортные операции id клиента; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Клиенты-Транспортные операции" ALTER COLUMN "id клиента" SET DEFAULT nextval('public."Клиенты-Транспортные _id клиента_seq"'::regclass);


--
-- TOC entry 4702 (class 2604 OID 27212)
-- Name: Клиенты-Транспортные операции id транспортной операции; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Клиенты-Транспортные операции" ALTER COLUMN "id транспортной операции" SET DEFAULT nextval('public."Клиенты-Транспо_id транспортной _seq"'::regclass);


--
-- TOC entry 4690 (class 2604 OID 27163)
-- Name: Маршруты id маршрута; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Маршруты" ALTER COLUMN "id маршрута" SET DEFAULT nextval('public."Маршруты_id маршрута_seq"'::regclass);


--
-- TOC entry 4685 (class 2604 OID 27145)
-- Name: Оплаты id оплаты; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Оплаты" ALTER COLUMN "id оплаты" SET DEFAULT nextval('public."Оплаты_id оплаты_seq"'::regclass);


--
-- TOC entry 4686 (class 2604 OID 27146)
-- Name: Оплаты id клиента; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Оплаты" ALTER COLUMN "id клиента" SET DEFAULT nextval('public."Оплаты_id клиента_seq"'::regclass);


--
-- TOC entry 4687 (class 2604 OID 27147)
-- Name: Оплаты id транспортной операции; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Оплаты" ALTER COLUMN "id транспортной операции" SET DEFAULT nextval('public."Оплаты_id транспортной операции_seq"'::regclass);


--
-- TOC entry 4695 (class 2604 OID 27189)
-- Name: Транспортные операции id транспортной операции; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Транспортные операции" ALTER COLUMN "id транспортной операции" SET DEFAULT nextval('public."Транспортные оп_id транспортной _seq"'::regclass);


--
-- TOC entry 4696 (class 2604 OID 27190)
-- Name: Транспортные операции id маршрута; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Транспортные операции" ALTER COLUMN "id маршрута" SET DEFAULT nextval('public."Транспортные операци_id маршрута_seq"'::regclass);


--
-- TOC entry 4691 (class 2604 OID 27171)
-- Name: Транспортные средства id транспортного средства; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Транспортные средства" ALTER COLUMN "id транспортного средства" SET DEFAULT nextval('public."Транспортные ср_id транспортного_seq"'::regclass);


--
-- TOC entry 4692 (class 2604 OID 27172)
-- Name: Транспортные средства id транспортной операции; Type: DEFAULT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Транспортные средства" ALTER COLUMN "id транспортной операции" SET DEFAULT nextval('public."Транспортные ср_id транспортной _seq"'::regclass);


--
-- TOC entry 4882 (class 0 OID 27152)
-- Dependencies: 223
-- Data for Name: Водители; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Водители" ("id водителя", "ФИО", "Возраст", "Стаж вождения", "Номер водительского удостоверени", "id транспортной операции") FROM stdin;
1	Иванов Иван Иванович	35	15	AB1234567	1
2	Петров Петр Петрович	40	20	CD2345678	2
3	Сидоров Алексей Николаевич	29	10	EF3456789	3
4	Козлов Дмитрий Олегович	45	25	GH4567890	4
5	Морозов Сергей Викторович	38	18	IJ5678901	5
6	Антонов Антон Антонович	33	12	KL6789012	6
7	Белов Виктор Сергеевич	50	30	MN7890123	7
8	Гаврилов Андрей Павлович	41	22	OP8901234	8
9	Дмитриев Олег Евгеньевич	36	17	QR9012345	9
10	Егоров Василий Николаевич	28	9	ST0123456	10
11	Жуков Михаил Петрович	47	26	UV1234567	11
12	Зайцев Николай Андреевич	32	14	WX2345678	12
13	Исаев Станислав Геннадьевич	44	23	YZ3456789	13
14	Капустин Федор Алексеевич	39	19	AB4567890	14
15	Лазарев Геннадий Владимирович	42	21	CD5678901	15
16	Михайлов Артем Сергеевич	31	11	EF6789012	16
17	Никитин Сергей Петрович	34	13	GH7890123	17
18	Орлов Виктор Андреевич	48	28	IJ8901234	18
19	Павлов Алексей Дмитриевич	37	16	KL9012345	19
20	Романов Артем Валентинович	29	10	MN0123456	20
21	Семенов Иван Григорьевич	46	27	OP1234567	21
22	Тихонов Олег Вячеславович	30	8	QR2345678	22
23	Ушаков Николай Игоревич	43	24	ST3456789	23
24	Федоров Петр Васильевич	35	15	UV4567890	24
25	Харитонов Максим Геннадьевич	49	29	WX5678901	25
26	Цветков Андрей Павлович	38	18	YZ6789012	26
27	Чернов Александр Олегович	45	26	AB7890123	27
28	Шестаков Виктор Аркадьевич	41	22	CD8901234	28
29	Щербаков Артем Владимирович	33	12	EF9012345	29
30	Юдин Олег Григорьевич	40	20	GH0123456	30
31	Яковлев Сергей Иванович	50	30	IJ1234567	31
\.


--
-- TOC entry 4890 (class 0 OID 27177)
-- Dependencies: 231
-- Data for Name: Грузы; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Грузы" ("id груза", "Название", "Вес", "Объём", "Дата погрузки", "id транспортной операции") FROM stdin;
1	Продукция сельского хозяйства	63.4	\N	2025-02-06	7
2	Строительные материалы	246.12	94.95	2025-02-24	2
3	Продукты питания	999.29	\N	2025-02-06	10
4	Офисная мебель	745.34	56.26	2025-02-26	7
5	Электронные устройства	473.8	42.29	2025-02-15	7
6	Стеклянные изделия	582.5	\N	2025-02-10	1
7	Автозапчасти	320.75	12.6	2025-02-18	3
8	Текстильная продукция	654.32	87.1	2025-02-22	9
9	Пластиковые трубы	123.98	18.9	2025-02-13	5
10	Деревянные панели	245.6	\N	2025-02-19	4
11	Бытовая техника	413.12	73.55	2025-02-16	8
12	Металлические конструкции	765.25	90.3	2025-02-21	6
13	Продукция агропромышленности	290.78	\N	2025-02-14	2
14	Химикаты	510.89	55.44	2025-02-20	10
15	Косметика и парфюмерия	820.6	\N	2025-02-17	1
16	Автозапчасти	325.43	21.2	2025-02-23	7
17	Книги и печатная продукция	105.2	\N	2025-02-25	3
18	Детские игрушки	600.34	66.8	2025-02-08	9
19	Мебель для дома	413.67	\N	2025-02-09	4
20	Фармацевтические препараты	256.9	80.5	2025-02-12	6
21	Упаковочные материалы	391.12	\N	2025-02-11	8
22	Продукция для животных	112.34	23.6	2025-02-05	5
23	Стеклянные бутылки	800.78	45.2	2025-02-07	2
24	Строительные товары	567.9	\N	2025-02-10	7
25	Моторные жидкости	434.2	58.3	2025-02-18	3
26	Пищевая продукция	111.5	\N	2025-02-13	10
27	Запчасти для сельскохозяйственной техники	222.3	40.2	2025-02-20	4
28	Инструменты для ремонта	689.7	\N	2025-02-25	9
29	Грузовая техника	543.12	85.1	2025-02-22	1
30	Молочные продукты	678.34	\N	2025-02-19	8
31	Шины и колесные диски	234.78	37.5	2025-02-21	5
\.


--
-- TOC entry 4897 (class 0 OID 27196)
-- Dependencies: 238
-- Data for Name: Грузы-Транспортные средства; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Грузы-Транспортные средства" (id, "id груза", "id транспортного средства") FROM stdin;
1	1	1
2	2	2
3	3	3
4	4	4
5	5	5
6	6	6
7	7	7
8	8	8
9	9	1
10	10	2
11	11	3
12	12	4
13	13	5
14	14	6
15	15	7
16	16	8
17	17	1
18	18	2
19	19	3
20	20	4
21	21	5
22	22	6
23	23	7
24	24	8
25	25	1
26	26	2
27	27	3
28	28	4
29	29	5
30	30	6
31	31	7
\.


--
-- TOC entry 4875 (class 0 OID 27133)
-- Dependencies: 216
-- Data for Name: Клиенты; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Клиенты" ("id клиента", "Название организации", "Адрес", "Номер телефона", "Адрес электронной почты") FROM stdin;
1	БелТрансЛогистик	Минск, ул. Логистическая, 10	+375291112201	contact@btl.by
2	ГрузЭкспресс	Гомель, ул. Центральная, 5	+375291112202	info@gruzexpress.by
3	ТрансАвто	Витебск, ул. Советская, 15	+375291112203	sales@transauto.by
4	ЛогистикСервис	Брест, ул. Транспортная, 12	+375291112204	logistic@ls.by
5	ГлобалКарго	Гродно, ул. Складская, 8	+375291112205	global@cargo.by
6	ТрансЛогист	Минск, ул. Промышленная, 25	+375291112206	info@translogist.by
7	ЭкспрессКарго	Гомель, ул. Погрузочная, 30	+375291112207	support@expresscargo.by
8	ФрахтСервис	Витебск, ул. Складская, 14	+375291112208	contact@frachtservice.by
9	СкороДоставка	Брест, ул. Магистральная, 22	+375291112209	info@skorodostavka.by
10	Европейские перевозки	Гродно, ул. Логистическая, 5	+375291112210	service@eurocargo.by
11	БелТрансСнаб	Минск, ул. Техническая, 17	+375291112211	contact@btsnab.by
12	ЛогистикПро	Гомель, ул. Грузовая, 40	+375291112212	info@logisticpro.by
13	ТранспортПлюс	Витебск, ул. Дальняя, 11	+375291112213	support@transportplus.by
14	КаргоБел	Брест, ул. Перевозочная, 19	+375291112214	service@cargobel.by
15	БелТрансСервис	Гродно, ул. Погрузочная, 7	+375291112215	contact@beltransservice.by
16	ФорвардТранс	Минск, ул. Логистическая, 33	+375291112216	info@forwardtrans.by
17	ТрансГарант	Гомель, ул. Путевая, 8	+375291112217	support@transgarant.by
18	ГрузПартнер	Витебск, ул. Магистральная, 21	+375291112218	service@gruzpartner.by
19	Скоростная логистика	Брест, ул. Грузовая, 26	+375291112219	info@fastlogistics.by
20	БелТрансЭкспресс	Гродно, ул. Доставочная, 12	+375291112220	contact@beltransexpress.by
21	ТранспЛайн	Минск, ул. Грузовая, 37	+375291112221	support@transpline.by
22	ЭкспедиторСервис	Гомель, ул. Магистральная, 13	+375291112222	service@expeditor.by
23	ЛогистБел	Витебск, ул. Перевозочная, 18	+375291112223	contact@logistbel.by
24	ФрахтЛайн	Брест, ул. Центральная, 9	+375291112224	info@frachtline.by
25	МегаТранс	Гродно, ул. Логистическая, 15	+375291112225	support@megatrans.by
26	ЕвроТранс	Минск, ул. Международная, 29	+375291112226	service@eurotrans.by
27	Транспортное агентство	Гомель, ул. Транспортная, 20	+375291112227	contact@transportagency.by
28	Грузовая логистика	Витебск, ул. Погрузочная, 32	+375291112228	info@gruzlogistic.by
29	ФрахтБел	Брест, ул. Грузовая, 16	+375291112229	support@frachtbel.by
30	КаргоСервис	Гродно, ул. Транспортная, 23	+375291112230	service@cargoservice.by
31	БелАвтоЛогистик	Минск, ул. Автопарк, 5	+375291112231	info@belautolog.by
32	ГрузИнтерТранс	Гомель, ул. Грузовая, 10	+375291112232	support@gruzintertrans.by
33	Логистический Центр	Витебск, ул. Промышленная, 14	+375291112233	contact@logisticcenter.by
\.


--
-- TOC entry 4901 (class 0 OID 27207)
-- Dependencies: 242
-- Data for Name: Клиенты-Транспортные операции; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Клиенты-Транспортные операции" (id, "id клиента", "id транспортной операции") FROM stdin;
1	1	1
2	1	2
3	2	3
4	2	4
5	3	5
6	3	6
7	4	7
8	4	8
9	5	9
10	6	10
11	6	11
12	7	12
13	7	13
14	8	14
15	8	15
16	9	16
17	10	17
18	10	18
19	11	19
20	12	20
21	12	21
22	13	22
23	13	23
24	14	24
25	15	25
26	15	26
27	16	27
28	17	28
29	18	29
30	19	30
31	20	31
32	21	1
33	22	2
34	23	3
35	24	4
36	25	5
37	26	6
38	27	7
39	28	8
40	29	9
41	30	10
42	31	11
\.


--
-- TOC entry 4884 (class 0 OID 27160)
-- Dependencies: 225
-- Data for Name: Маршруты; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Маршруты" ("id маршрута", "Точка отправления", "Точка прибытия", "Расстояние", "Время в пути") FROM stdin;
1	Минск	Гомель	300.5	05:30:00
2	Минск	Брест	400.2	06:00:00
3	Минск	Гродно	270.8	04:45:00
4	Минск	Витебск	250.3	04:00:00
5	Гомель	Минск	300.5	05:30:00
6	Гомель	Брест	450	07:00:00
7	Гомель	Гродно	330.4	06:10:00
8	Гомель	Витебск	380	06:40:00
9	Брест	Минск	400.2	06:00:00
10	Брест	Гомель	450	07:00:00
11	Брест	Гродно	160.3	03:20:00
12	Брест	Витебск	380.4	06:20:00
13	Гродно	Минск	270.8	04:45:00
14	Гродно	Гомель	330.4	06:10:00
15	Гродно	Брест	160.3	03:20:00
16	Гродно	Витебск	300	05:30:00
17	Витебск	Минск	250.3	04:00:00
18	Витебск	Гомель	380	06:40:00
19	Витебск	Брест	380.4	06:20:00
20	Витебск	Гродно	300	05:30:00
21	Минск	Смолевичи	40	00:45:00
22	Гомель	Смолевичи	320	05:00:00
23	Брест	Смолевичи	430	07:30:00
24	Гродно	Смолевичи	350	06:10:00
25	Витебск	Смолевичи	370	06:20:00
26	Минск	Прага	1500	20:00:00
27	Гомель	Прага	1600	21:00:00
28	Брест	Прага	1400	19:00:00
29	Гродно	Прага	1550	20:30:00
30	Витебск	Прага	1650	21:30:00
31	Минск	Берлин	1300	18:00:00
32	Гомель	Берлин	1400	19:00:00
33	Брест	Берлин	1200	17:30:00
34	Гродно	Берлин	1350	18:30:00
35	Витебск	Берлин	1450	19:30:00
\.


--
-- TOC entry 4879 (class 0 OID 27142)
-- Dependencies: 220
-- Data for Name: Оплаты; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Оплаты" ("id оплаты", "Сумма", "Дата оплаты", "Способ оплаты", "id клиента", "id транспортной операции") FROM stdin;
1	150	2025-03-01	Банковский перевод	1	1
2	250	2025-03-02	Наличные	2	2
3	300	2025-03-03	Кредитная карта	3	3
4	100	2025-03-04	Электронный кошелек	4	4
5	200	2025-03-05	Банковский перевод	5	5
6	350	2025-03-06	Наличные	6	6
7	120	2025-03-07	Кредитная карта	7	7
8	180	2025-03-08	Электронный кошелек	8	8
9	220	2025-03-09	Банковский перевод	9	9
10	160	2025-03-10	Наличные	10	10
11	240	2025-03-11	Кредитная карта	11	11
12	130	2025-03-12	Электронный кошелек	12	12
13	190	2025-03-13	Банковский перевод	13	13
14	210	2025-03-14	Наличные	14	14
15	300	2025-03-15	Кредитная карта	15	15
16	140	2025-03-16	Электронный кошелек	16	16
17	230	2025-03-17	Банковский перевод	17	17
18	260	2025-03-18	Наличные	18	18
19	280	2025-03-19	Кредитная карта	19	19
20	350	2025-03-20	Электронный кошелек	20	20
21	110	2025-03-21	Банковский перевод	21	21
22	150	2025-03-22	Наличные	22	22
23	200	2025-03-23	Кредитная карта	23	23
24	250	2025-03-24	Электронный кошелек	24	24
25	220	2025-03-25	Банковский перевод	25	25
26	280	2025-03-26	Наличные	26	26
27	300	2025-03-27	Кредитная карта	27	27
28	130	2025-03-28	Электронный кошелек	28	28
29	140	2025-03-29	Банковский перевод	29	29
30	160	2025-03-30	Наличные	30	30
31	190	2025-03-31	Кредитная карта	31	31
\.


--
-- TOC entry 4893 (class 0 OID 27186)
-- Dependencies: 234
-- Data for Name: Транспортные операции; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Транспортные операции" ("id транспортной операции", "Статус", "Ожидаемое время доставки", "Дата прибытия", "id маршрута") FROM stdin;
1	В процессе	12:30:00	2025-02-05	3
2	Завершена	14:30:00	2025-02-06	4
3	В процессе	15:00:00	2025-02-07	5
4	Завершена	17:30:00	2025-02-08	6
5	В процессе	11:00:00	2025-02-09	7
6	Завершена	16:30:00	2025-02-10	8
7	В процессе	12:45:00	2025-02-11	9
8	Завершена	13:30:00	2025-02-12	10
9	В процессе	14:00:00	2025-02-13	1
10	Завершена	15:30:00	2025-02-14	2
11	В процессе	16:15:00	2025-02-15	3
12	Завершена	17:00:00	2025-02-16	4
13	В процессе	11:30:00	2025-02-17	5
14	Завершена	14:45:00	2025-02-18	6
15	В процессе	13:15:00	2025-02-19	7
16	Завершена	15:00:00	2025-02-20	8
17	В процессе	14:30:00	2025-02-21	9
18	Завершена	12:00:00	2025-02-22	10
19	В процессе	11:45:00	2025-02-23	1
20	Завершена	13:30:00	2025-02-24	2
21	В процессе	16:00:00	2025-02-25	3
22	Завершена	14:30:00	2025-02-26	4
23	В процессе	17:00:00	2025-02-27	5
24	Завершена	11:00:00	2025-02-28	6
25	В процессе	15:30:00	2025-03-01	7
26	Завершена	13:00:00	2025-03-02	8
27	В процессе	16:30:00	2025-03-03	9
28	Завершена	12:15:00	2025-03-04	10
29	В процессе	14:00:00	2025-03-05	1
30	Завершена	15:30:00	2025-03-06	2
31	В процессе	16:00:00	2025-03-07	3
\.


--
-- TOC entry 4887 (class 0 OID 27168)
-- Dependencies: 228
-- Data for Name: Транспортные средства; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public."Транспортные средства" ("id транспортного средства", "Производитель", "Модель", "Грузоподъёмность", "Регистрационный номер", "id транспортной операции") FROM stdin;
1	Mercedes	Sprinter	3500	A123BC	1
2	Volvo	FH16	8000	B234CD	2
3	MAN	TGS	6500	C345DE	3
4	Scania	R450	7500	D456EF	4
5	Renault	Master	3500	E567FG	5
6	Iveco	EuroCargo	5000	F678GH	6
7	Mercedes	Atego	4000	G789HI	7
8	Volvo	FMX	7000	H890IJ	8
9	MAN	TGX	8500	I901JK	9
10	Scania	S500	7600	J012KL	10
11	Renault	T460	6800	K123LM	11
12	Iveco	Stralis	7200	L234MN	12
13	Mercedes	Actros	9500	M345NO	13
14	Volvo	VNL	8000	N456OP	14
15	MAN	Lions Coach	9000	O567PQ	15
16	Scania	G410	7000	P678QR	16
17	Renault	T520	6500	Q789RS	17
18	Iveco	Daily	3000	R890ST	18
19	Mercedes	Vito	2800	S901TU	19
20	Volvo	V90	5500	T012UV	20
21	MAN	F2000	6400	U123VW	21
22	Scania	L Series	5300	V234WX	22
23	Renault	K Range	8500	W345XY	23
24	Iveco	EuroTech	7800	X456YZ	24
25	Mercedes	Benz	4000	Y567ZA	25
26	Volvo	Globetrotter	9500	Z678AB	26
27	MAN	ClubTruck	6600	A789BC	27
28	Scania	V8	9200	B890CD	28
29	Renault	Range T	6700	C901DE	29
30	Iveco	EuroStar	7300	D012EF	30
31	Mercedes	Zetros	10000	E123FG	31
\.


--
-- TOC entry 4927 (class 0 OID 0)
-- Dependencies: 221
-- Name: Водители_id водителя_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Водители_id водителя_seq"', 31, true);


--
-- TOC entry 4928 (class 0 OID 0)
-- Dependencies: 222
-- Name: Водители_id транспортной операци_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Водители_id транспортной операци_seq"', 1, false);


--
-- TOC entry 4929 (class 0 OID 0)
-- Dependencies: 237
-- Name: Грузы-Транспорт_id транспортного_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Грузы-Транспорт_id транспортного_seq"', 1, false);


--
-- TOC entry 4930 (class 0 OID 0)
-- Dependencies: 236
-- Name: Грузы-Транспортные сред_id груза_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Грузы-Транспортные сред_id груза_seq"', 1, false);


--
-- TOC entry 4931 (class 0 OID 0)
-- Dependencies: 235
-- Name: Грузы-Транспортные средства_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Грузы-Транспортные средства_id_seq"', 31, true);


--
-- TOC entry 4932 (class 0 OID 0)
-- Dependencies: 229
-- Name: Грузы_id груза_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Грузы_id груза_seq"', 31, true);


--
-- TOC entry 4933 (class 0 OID 0)
-- Dependencies: 230
-- Name: Грузы_id транспортной операции_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Грузы_id транспортной операции_seq"', 1, false);


--
-- TOC entry 4934 (class 0 OID 0)
-- Dependencies: 241
-- Name: Клиенты-Транспо_id транспортной _seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Клиенты-Транспо_id транспортной _seq"', 1, false);


--
-- TOC entry 4935 (class 0 OID 0)
-- Dependencies: 240
-- Name: Клиенты-Транспортные _id клиента_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Клиенты-Транспортные _id клиента_seq"', 1, false);


--
-- TOC entry 4936 (class 0 OID 0)
-- Dependencies: 239
-- Name: Клиенты-Транспортные операции_id_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Клиенты-Транспортные операции_id_seq"', 42, true);


--
-- TOC entry 4937 (class 0 OID 0)
-- Dependencies: 215
-- Name: Клиенты_id клиента_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Клиенты_id клиента_seq"', 33, true);


--
-- TOC entry 4938 (class 0 OID 0)
-- Dependencies: 224
-- Name: Маршруты_id маршрута_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Маршруты_id маршрута_seq"', 1, true);


--
-- TOC entry 4939 (class 0 OID 0)
-- Dependencies: 218
-- Name: Оплаты_id клиента_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Оплаты_id клиента_seq"', 1, false);


--
-- TOC entry 4940 (class 0 OID 0)
-- Dependencies: 217
-- Name: Оплаты_id оплаты_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Оплаты_id оплаты_seq"', 31, true);


--
-- TOC entry 4941 (class 0 OID 0)
-- Dependencies: 219
-- Name: Оплаты_id транспортной операции_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Оплаты_id транспортной операции_seq"', 1, false);


--
-- TOC entry 4942 (class 0 OID 0)
-- Dependencies: 232
-- Name: Транспортные оп_id транспортной _seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Транспортные оп_id транспортной _seq"', 31, true);


--
-- TOC entry 4943 (class 0 OID 0)
-- Dependencies: 233
-- Name: Транспортные операци_id маршрута_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Транспортные операци_id маршрута_seq"', 1, false);


--
-- TOC entry 4944 (class 0 OID 0)
-- Dependencies: 226
-- Name: Транспортные ср_id транспортного_seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Транспортные ср_id транспортного_seq"', 31, true);


--
-- TOC entry 4945 (class 0 OID 0)
-- Dependencies: 227
-- Name: Транспортные ср_id транспортной _seq; Type: SEQUENCE SET; Schema: public; Owner: postgres
--

SELECT pg_catalog.setval('public."Транспортные ср_id транспортной _seq"', 1, false);


--
-- TOC entry 4708 (class 2606 OID 27158)
-- Name: Водители Водители_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Водители"
    ADD CONSTRAINT "Водители_pkey" PRIMARY KEY ("id водителя");


--
-- TOC entry 4718 (class 2606 OID 27203)
-- Name: Грузы-Транспортные средства Грузы-Транспортные средства_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Грузы-Транспортные средства"
    ADD CONSTRAINT "Грузы-Транспортные средства_pkey" PRIMARY KEY (id);


--
-- TOC entry 4714 (class 2606 OID 27183)
-- Name: Грузы Грузы_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Грузы"
    ADD CONSTRAINT "Грузы_pkey" PRIMARY KEY ("id груза");


--
-- TOC entry 4720 (class 2606 OID 27214)
-- Name: Клиенты-Транспортные операции Клиенты-Транспортные операции_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Клиенты-Транспортные операции"
    ADD CONSTRAINT "Клиенты-Транспортные операции_pkey" PRIMARY KEY (id);


--
-- TOC entry 4704 (class 2606 OID 27138)
-- Name: Клиенты Клиенты_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Клиенты"
    ADD CONSTRAINT "Клиенты_pkey" PRIMARY KEY ("id клиента");


--
-- TOC entry 4710 (class 2606 OID 27165)
-- Name: Маршруты Маршруты_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Маршруты"
    ADD CONSTRAINT "Маршруты_pkey" PRIMARY KEY ("id маршрута");


--
-- TOC entry 4706 (class 2606 OID 27149)
-- Name: Оплаты Оплаты_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Оплаты"
    ADD CONSTRAINT "Оплаты_pkey" PRIMARY KEY ("id оплаты");


--
-- TOC entry 4716 (class 2606 OID 27192)
-- Name: Транспортные операции Транспортные операции_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Транспортные операции"
    ADD CONSTRAINT "Транспортные операции_pkey" PRIMARY KEY ("id транспортной операции");


--
-- TOC entry 4712 (class 2606 OID 27174)
-- Name: Транспортные средства Транспортные средства_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Транспортные средства"
    ADD CONSTRAINT "Транспортные средства_pkey" PRIMARY KEY ("id транспортного средства");


--
-- TOC entry 4727 (class 2606 OID 27245)
-- Name: Грузы-Транспортные средства Грузы_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Грузы-Транспортные средства"
    ADD CONSTRAINT "Грузы_fkey" FOREIGN KEY ("id груза") REFERENCES public."Грузы"("id груза") NOT VALID;


--
-- TOC entry 4721 (class 2606 OID 27215)
-- Name: Оплаты Клиенты_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Оплаты"
    ADD CONSTRAINT "Клиенты_fkey" FOREIGN KEY ("id клиента") REFERENCES public."Клиенты"("id клиента") NOT VALID;


--
-- TOC entry 4729 (class 2606 OID 27255)
-- Name: Клиенты-Транспортные операции Клиенты_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Клиенты-Транспортные операции"
    ADD CONSTRAINT "Клиенты_fkey" FOREIGN KEY ("id клиента") REFERENCES public."Клиенты"("id клиента") NOT VALID;


--
-- TOC entry 4726 (class 2606 OID 27240)
-- Name: Транспортные операции Маршруты_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Транспортные операции"
    ADD CONSTRAINT "Маршруты_fkey" FOREIGN KEY ("id маршрута") REFERENCES public."Маршруты"("id маршрута") NOT VALID;


--
-- TOC entry 4722 (class 2606 OID 27220)
-- Name: Оплаты Транспортные операции_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Оплаты"
    ADD CONSTRAINT "Транспортные операции_fkey" FOREIGN KEY ("id транспортной операции") REFERENCES public."Транспортные операции"("id транспортной операции") NOT VALID;


--
-- TOC entry 4723 (class 2606 OID 27225)
-- Name: Водители Транспортные операции_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Водители"
    ADD CONSTRAINT "Транспортные операции_fkey" FOREIGN KEY ("id транспортной операции") REFERENCES public."Транспортные операции"("id транспортной операции") NOT VALID;


--
-- TOC entry 4724 (class 2606 OID 27230)
-- Name: Транспортные средства Транспортные операции_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Транспортные средства"
    ADD CONSTRAINT "Транспортные операции_fkey" FOREIGN KEY ("id транспортной операции") REFERENCES public."Транспортные операции"("id транспортной операции") NOT VALID;


--
-- TOC entry 4725 (class 2606 OID 27235)
-- Name: Грузы Транспортные операции_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Грузы"
    ADD CONSTRAINT "Транспортные операции_fkey" FOREIGN KEY ("id транспортной операции") REFERENCES public."Транспортные операции"("id транспортной операции") NOT VALID;


--
-- TOC entry 4730 (class 2606 OID 27260)
-- Name: Клиенты-Транспортные операции Транспортные операции_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Клиенты-Транспортные операции"
    ADD CONSTRAINT "Транспортные операции_fkey" FOREIGN KEY ("id транспортной операции") REFERENCES public."Транспортные операции"("id транспортной операции") NOT VALID;


--
-- TOC entry 4728 (class 2606 OID 27250)
-- Name: Грузы-Транспортные средства Транспортные средства_fkey; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public."Грузы-Транспортные средства"
    ADD CONSTRAINT "Транспортные средства_fkey" FOREIGN KEY ("id транспортного средства") REFERENCES public."Транспортные средства"("id транспортного средства") NOT VALID;


-- Completed on 2025-03-06 04:03:56

--
-- PostgreSQL database dump complete
--


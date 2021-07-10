CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

create table destino (
  cidade varchar(50),
  pais   varchar(50),
  constraint pk_destino primary key (cidade, pais)
);

create table monumento (
  nome      varchar(100),
  cidade    varchar(50),
  pais      varchar(50),
  descricao text,

  constraint pk_monumento         primary key (nome, cidade, pais),
  constraint fk_monumento_destino foreign key (cidade, pais)      references destino(cidade, pais)
                  on delete cascade
                  on update cascade
);

create table museu (
  cadastro_nacional         varchar(20) primary key,
  nome                      varchar(50),
  telefone                  varchar(20),
  logradouro                varchar(50),
  numero                    int8,
  codigo_postal             varchar(9),
  ajuda_deficiente_visao    bool        default false,
  ajuda_deficiente_auditivo bool        default false,
  cidade                    varchar(50) not null,
  pais                      varchar(50) not null,

  constraint fk_museu_destino foreign key (cidade, pais) references destino(cidade, pais)
                              on delete cascade
                              on update cascade
);

create table idioma_museu (
  idioma varchar(20),
  museu  varchar(20),

  constraint pk_idioma_museu primary key (idioma, museu),
  constraint fk_idioma_museu foreign key (museu)         references museu(cadastro_nacional)
                             on delete cascade
                             on update cascade
);

create table exposicao (
  museu           varchar(20),
  nome            varchar(30),
  data_de_inicio  date not null,
  data_de_termino date,
  descricao       text,

  constraint pk_exposicao           primary key (museu, nome),
  constraint fk_exposicao_museu     foreign key (museu)       references museu(cadastro_nacional)
                                    on delete cascade
                                    on update cascade,
  constraint ck_inicio_antes_de_fim check       (data_de_termino > data_de_inicio)
);

create table origem (
  pais   varchar(50),
  epoca  varchar(50),
  inicio date,
  fim    date,

  constraint pk_origem              primary key (pais, epoca),
  constraint ck_inicio_antes_de_fim check       (fim > inicio)
);

create table artista (
  nome                varchar(50),
  data_de_nascimento  date,
  data_de_falecimento date,
  biografia           text,

  constraint pk_artista             primary key (nome, data_de_nascimento),
  constraint ck_inicio_antes_de_fim check       (data_de_nascimento < data_de_falecimento)
);

create table obra (
  nome                varchar(100),
  museu               varchar(20) not null,
  exposicao           varchar(30) not null,
  artista             varchar(50),
  data_de_nascimento  date,
  origem              varchar(50),
  epoca               varchar(50),
  descricao           text,
  data_de_criacao     date,
  categoria           varchar(9),

  constraint pk_obra           primary key (nome, artista, data_de_nascimento),
  constraint fk_obra_origem    foreign key (origem, epoca)
                               references origem(pais, epoca)
                               on delete set null
                               on update cascade,
  constraint fk_obra_artista   foreign key (artista, data_de_nascimento)
                               references artista(nome, data_de_nascimento)
                               on delete cascade
                               on update cascade,
  constraint fk_obra_exposicao foreign key (exposicao, museu)
                               references exposicao(nome, museu)
                               on delete cascade
                               on update cascade,
  constraint ck_categoria_obra check (categoria in ('pintura','escultura','documento','artefato','fossil'))
);

create table guia (
  email           varchar(50) primary key,
  senha           varchar(64),
  nome            varchar(50),
  telefone        varchar(20),
  logradouro      varchar(50),
  numero          int8,
  codigo_postal   varchar(9),
  cidade          varchar(50),
  pais            varchar(50),
  complemento     varchar(50),

    constraint ck_email_valido check (email ~* '^[A-Za-z0-9._%-]+@[A-Za-z0-9.-]+[.][A-Za-z]+$')
);

create table idioma_guia (
  idioma varchar(20),
  guia   varchar(50),

  constraint pk_idioma_guia primary key (guia, idioma),
  constraint fk_idioma_guia foreign key (guia)
                            references guia(email)
                            on delete cascade
                            on update cascade
);

create table visitante (
  email           varchar(50) primary key,
  senha           varchar(64),
  nome            varchar(50),
  telefone        varchar(20),
  logradouro      varchar(50),
  numero          int8,
  codigo_postal   varchar(9),
  cidade          varchar(50),
  pais            varchar(50),
  complemento     varchar(50),

    constraint ck_email_valido check (email ~* '^[A-Za-z0-9._%-]+@[A-Za-z0-9.-]+[.][A-Za-z]+$')
);

create table visita_guiada (
  id              uuid primary key default uuid_generate_v4(),
  data_horario    timestamptz,
  guia            varchar(50),
  exposicao       varchar(30),
  museu           varchar(20),
  idioma          varchar(20),

  constraint sk_visita_guiada           unique (data_horario, guia, exposicao, museu),
  constraint fk_visita_guiada_exposicao foreign key (exposicao, museu)
                      references exposicao(nome, museu)
                      on delete cascade
                      on update cascade,
  constraint fk_visita_guiada_guia      foreign key (guia)
                        references guia(email)
                        on delete cascade
                        on update cascade
);

create table grupo_visita (
    visitante      varchar(50),
    visita_guiada  uuid,

    constraint pk_grupo_visita               primary key (visita_guiada, visitante),
    constraint fk_grupo_visita_visita_guiada foreign key (visitante)
                                             references visitante(email)
                                             on delete cascade
                                             on update cascade,
    constraint fk_visita_guiada_visitante    foreign key (visitante)
                                             references visitante(email)
                                             on delete cascade
                                             on update cascade
);

create table restaurante (
  cadastro_nacional         varchar(20) primary key,
  museu                     varchar(20) not null,
  nome                      varchar(50),
  horario_abertura          timetz,
  horario_fechamento		  timetz,
  culinaria1      		  varchar(30),
  culinaria2      		  varchar(30),
  culinaria3      		  varchar(30),

  constraint fk_restaurante_museu    foreign key (museu)
                                     references museu(cadastro_nacional)
                                     on delete cascade
                                     on update cascade,
  constraint ck_abre_antes_de_fechar check (horario_abertura < horario_fechamento)
);

create table reserva_restaurante (
  visitante    varchar(50),
  data_horario timestamptz,
  restaurante  varchar(20),

  constraint pk_reserva_restaurante primary key (visitante, data_horario, restaurante),
    constraint fk_reserva_restaurante_visitante   foreign key (visitante)
                                                  references visitante(email)
                                                  on delete cascade
                                                  on update cascade,
    constraint fk_reserva_restaurante_restaurante foreign key (restaurante)
                                                  references restaurante(cadastro_nacional)
                                                  on delete cascade
                                                  on update cascade
);

create table viagem (
  visitante          varchar(50),
  data_horario       timestamptz,
  cidade             varchar(50),
  pais               varchar(50),
  meio_de_transporte varchar(20),

  constraint ck_meio_de_transporte check (meio_de_transporte
                   in ('aviao', 'trem', 'barco', 'carro', 'onibus')),
  constraint pk_viagem           primary key (visitante, data_horario, cidade, pais),
  constraint fk_viagem_visitante foreign key (visitante)
                   references visitante(email)
                   on delete cascade
                   on update cascade,
  constraint fk_viagem_destino   foreign key (cidade, pais)
                   references destino(cidade, pais)
                   on delete cascade
                   on update cascade
);

create table hotel (
  cadastro_nacional   varchar(20) primary key,
  nome                varchar(50),
  telefone            varchar(20),
  logradouro          varchar(50),
  numero              int8,
  codigo_postal       varchar(9),
  cidade              varchar(50) not null,
  pais                varchar(50) not null,

  constraint fk_hotel_destino foreign key (cidade, pais)
                              references destino(cidade, pais)
                              on delete cascade
                              on update cascade
);

create table quarto (
  camas          int,
  preco_por_cama money,
  numero         int,
  hotel          varchar(20),

  constraint pk_quarto       primary key (numero, hotel),
  constraint fk_quarto_hotel foreign key (hotel)
                             references hotel(cadastro_nacional)
                             on delete cascade
                             on update cascade
);

create table reserva_quarto (
  visitante       varchar(50),
  data_de_inicio  date,
  data_de_termino date,
  quarto          int,
  hotel           varchar(20),

  constraint pk_reserva_quarto           primary key (visitante, data_de_inicio, quarto, hotel),
  constraint fk_reserva_quarto_visitante foreign key (visitante)
                                         references visitante(email)
                                         on delete cascade
                                         on update cascade,
  constraint fk_reserva_quarto_quarto    foreign key (quarto, hotel)
                                         references quarto(numero, hotel)
                                         on delete cascade
                                         on update cascade,
  constraint ck_inicio_antes_de_termino  check       (data_de_termino > data_de_inicio)
);

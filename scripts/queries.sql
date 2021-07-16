# Visita guiadas em uma exposicao com possiveis idiomas que não esteja lotado {{{;
select * from visita_guiada vg
  where exposicao = 'painting and sculpture' and museu = 'MU005'
  and idioma in ('Frances', 'Espanhol')
  and (select count(*) from grupo_visita where visita_guiada = vg.id) < 20;
# }}};

# Consultar obras de cada país de cada categoria, agrupando por museu {{{;
select count(o.nome), o.categoria, o.exposicao, m.nome, m.pais
  from obra o
  join museu m
    on m.cadastro_nacional = o.museu
  group by m.pais, m.nome, o.exposicao, o.categoria
  order by m.pais;
# }}};

# Consultar a média de ganho dos hotéis em que a média foi maior que a média de ganho de todos os hoteis juntos em determinado periodo de tempo {{{;
select * from (
  select
    avg(rq.preco_total::numeric)::money as avg_income,
    rq.hotel,
    h.nome,
    h.pais
  from reserva_quarto rq
  join hotel h on rq.hotel = h.cadastro_nacional
  where data_de_inicio >= '2016-01-01' and data_de_inicio < '2020-01-01'
  group by rq.hotel, h.nome, h.pais) avgs
where avg_income::numeric > (
  select avg(rq.preco_total::numeric)
  from reserva_quarto rq
);
# }}};

# Obter os monumentos mais visitados nas ultimas X viagens {{{;
select
  count(visitante) viagens_para_monumento,
  nome,
  cidade,
  pais
from (
  select
    m.nome,
    m.cidade,
    m.pais,
    v.visitante
  from monumento m
  left join viagem v
    on m.cidade = v.cidade
    and m.pais = v.pais
  order by v.data_horario
) resul
group by nome, cidade, pais
order by viagens_para_monumento desc;
# }}};

# Obter lista de guias e idiomas que falam nas visitas guiadas dentro dos destinos que um visitante irá visitar {{{;
select
  vg.data_horario,
  m.nome,
  g.nome,
  ig.idioma
from visita_guiada vg
join guia g
  on vg.guia = g.email
join idioma_guia ig
  on g.email = ig.guia
join museu m
  on vg.museu = m.cadastro_nacional
where m.cidade in (
  select cidade
  from viagem
  where visitante = 'uchaw.rash193s@21jag.com'
)
order by vg.museu, idioma;
# }}};

# Contagens de obra do artista por categoria da obra em museus de locais que o visitante viajará para {{{;
select
  count(o.nome) n_obras,
  o.artista,
  o.categoria
from obra o
join museu m
  on m.cadastro_nacional = o.museu
where o.artista != 'Desconhecido'
  and m.cidade in (
    select cidade from viagem where visitante = 'uchaw.rash193s@21jag.com') group by o.artista, o.categoria order by n_obras desc, artista;
# }}};

# Verificar quais idiomas um museu dá suporte a mais que outro museu. {{{;
with mei as (
  select i.idioma, m.cadastro_nacional
  from museu m
  join idioma_museu i on i.museu = m.cadastro_nacional
)
select idioma from mei where cadastro_nacional = 'MU001'
except
select idioma from mei where cadastro_nacional = 'MU002';
# }}};

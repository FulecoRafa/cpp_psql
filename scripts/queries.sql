# Visita guiadas em uma exposicao com possiveis idiomas que não esteja lotado
select * from visita_guiada vg
  where exposicao = 'painting and sculpture' and museu = 'MU005'
  and idioma in ('Frances', 'Espanhol')
  and (select count(*) from grupo_visita where visita_guiada = vg.id) < 20;

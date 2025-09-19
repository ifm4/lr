from sqlalchemy import create_engine, text
from sqlalchemy.orm import Session

engine = create_engine('sqlite:///database.db', echo=True)

conn = engine.connect()
conn.execute(text('CREATE TABLE IF NOT EXISTS users (id int, username str)'))
conn.commit()


session = Session(engine)
session.execute(text('INSERT INTO users (id, username) VALUES (1, "John");'))
session.commit()

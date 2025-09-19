from sqlalchemy import create_engine, MetaData, Table, Column, Integer, String, insert

engine = create_engine("sqlite:///database.db", echo=True)

meta = MetaData()

service = Table(
    "service",
    meta,
    Column("id", Integer, primary_key=True),
    Column("name", String, nullable=False),
    Column("url", String, nullable=False),
)

meta.create_all(engine)

conn = engine.connect()

insert_statement = service.insert().values(name="first", url="https://first.fi/")
result = conn.execute(insert_statement)
conn.commit()

insert_statement = insert(service).values(name="second", url="https://second.se/")
result = conn.execute(insert_statement)
conn.commit()

insert_statement = service.insert().values(
    [
        {"name": "third", "url": "https://thi.rd/"},
        {"name": "fourth", "url": "https://four.th/"},
    ]
)

update_statement = (
    service.update().where(service.c.name == "first").values(url="https://fir.st")
)
result = conn.execute(update_statement)
conn.commit()

from sqlalchemy import create_engine, Integer, String, Float, Column, ForeignKey
from sqlalchemy.orm import declarative_base, sessionmaker, relationship

engine = create_engine("sqlite:///database.db", echo=True)

Base = declarative_base()


class Service(Base):
    __tablename__ = "services"
    id = Column(Integer, primary_key=True)
    name = Column(String, nullable=False)
    url = Column(String, nullable=False)

    check_results = relationship("CheckResult", back_populates="service")


class CheckResult(Base):
    __tablename__ = "check_results"
    id = Column(Integer, primary_key=True)
    service_id = Column(Integer, ForeignKey("services.id"))

    service = relationship("Service", back_populates="check_results")


Base.metadata.create_all(engine)

Session = sessionmaker(bind=engine)
session = Session()

new_service = Service(name='first', url='https://fir.st/')
session.add(new_service)

session.commit()

new_service = Service(name='second', url='https://seco.nd/')
session.add(new_service)
session.flush()

for i in range(3):
    new_check = CheckResult(service_id=new_service.id)
    session.add(new_check)
    session.commit()

print([check.id for check in new_service.check_results])

from sqlalchemy import (
    create_engine,
    text,
    Integer,
    String,
    DateTime,
    Column,
    ForeignKey,
)
from sqlalchemy.orm import declarative_base, sessionmaker, relationship


engine = create_engine("sqlite:///./data/app.db")  # os.getenv("DB_URL")?
Base = declarative_base()


class Service(Base):
    __tablename__ = "services"
    id = Column(Integer, primary_key=True)
    name = Column(String, nullable=False)
    url = Column(String, nullable=False)
    interval_s = Column(Integer)
    timeout_s = Column(Integer)
    created_at = Column(
        DateTime, server_default=text("CURRENT_TIMESTAMP"), nullable=False
    )

    check_results = relationship("CheckResult", back_populates="service")
    incidents = relationship("Incident", back_populates="service")


class CheckResult(Base):
    __tablename__ = "check_results"
    id = Column(Integer, primary_key=True)
    service_id = Column(Integer, ForeignKey("services.id"), nullable=False)
    ts = Column(DateTime, server_default=text("CURRENT_TIMESTAMP"), nullable=False)
    ok = Column(Integer)  # redundant?
    status_code = Column(Integer)
    latency_ms = Column(Integer)
    error_text = Column(String)

    service = relationship("Service", back_populates="check_results")

    # __table_args__ = Index("idx_svcid_ts", "service_id", "ts")


class Incident(Base):
    __tablename__ = "incidents"
    id = Column(Integer, primary_key=True)
    service_id = Column(Integer, ForeignKey("services.id"), nullable=False)
    opened_at = Column(DateTime)
    closed_at = Column(DateTime)
    fail_count = Column(Integer)
    is_open = Column(Integer)

    service = relationship("Service", back_populates="incidents")


Base.metadata.create_all(engine)
Session = sessionmaker(bind=engine)
session = Session()
session.commit()


def create_service(name: str, url: str, interval_s: int, timeout_s: int) -> Service: ...


def list_services() -> list[Service]: ...


def insert_check_result(
    service_id: int, ts, ok, status_code: int, latency_ms: int, error_text: str
) -> None: ...


def get_last_status(service_id: int) -> dict | None: ...


def get_history(service_id: int, limit: int) -> list[dict]: ...


if __name__ == "__main__":
    pass

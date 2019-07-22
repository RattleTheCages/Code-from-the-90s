#!/bin/ksh

# --------------------------------------------------------------------------
# --------------------------------------------------------------------------


if [[ (! -f /app/prod/bin/.global) || (! -r /app/prod/bin/.global) ]]
  then
    echo "Cannot find /app/prod/bin/.global"
    exit 1
fi
. /app/prod/bin/.global


# --------------------------------------------------------------------------
# --------------------------------------------------------------------------


isql -U${LOGON} -P${PASSWD} -D${DBNAME} -S${SERVER} -w 80 <<!
SET NOCOUNT ON

use tempdb
go

create table ENTERPRISE_INFO  (				-- The list of enterprises.
	ENTERPRISE_ID	int		PRIMARY KEY,	-- The field ENTERPRISE_ID is unique.
	DESCRIPTION	char(88)	NOT NULL,	-- A description of the enterprise.
	DESCRIPTION2	char(255)	NULL
)


create table ENTERPRISE_DIVISION_INFO  (		-- The list of divisions in an enterprise.
	DIVISION_ID	int		NOT NULL,	-- Different ENTERPRISE_IDs may have dupicate DIVISION_IDs.
	ENTERPRISE_ID	int		NOT NULL,	-- But any one ENTERPRISE_ID should have unique DIVISION_IDs.
	DESCRIPTION	char(88)	NOT NULL,	-- A description of the division.
	DESCRIPTION2	char(255)	NULL
)

create table ENTERPRISE_DIVISION_GROUP_INFO  (		-- The list of groups in a division.
	GROUP_ID	int		NOT NULL,	-- Different DIVISION_IDs may have dupicate GROUP_IDs.
	DIVISION_ID	int		NOT NULL,	-- But any one DIVISION_ID should have unique GROUP_IDs.
	ENTERPRISE_ID	int		NOT NULL,
	DESCRIPTION	char(88)	NOT NULL,
	DESCRIPTION2	char(255)	NULL
)



create table GROUP_PROJECT_INFO  (			-- The descriptions of projects in a group.
        PROJECT_ID	int		NOT NULL,	-- Different ENTERPRISE_IDs may have dupicate PROJECT_IDs.
	GROUP_ID	int		NOT NULL,	-- A group may have more than one project.
	DIVISION_ID	int		NOT NULL,	-- A division may have more than one project.
	ENTERPRISE_ID	int		NOT NULL,	-- An ENTERPRISE_ID may have many projects.
	DESCRIPTION	char(88)	NOT NULL,
	DESCRIPTION2	char(255)	NULL
)

create table GROUP_PROJECT_CREW  (			-- The listing of personnal on a project.
        PROJECT_ID	int		NOT NULL,
	GROUP_ID	int		NOT NULL,
	DIVISION_ID	int		NOT NULL,
	ENTERPRISE_ID	int		NOT NULL,
        PERSONNAL_ID	int		NOT NULL,	-- A person can be working on more than one project at once.
	TASK_ID		int		NOT NULL	-- A person may also be assigned more than one task.
)

create table GROUP_PROJECT_TASK_INFO  (			-- The descriptions of tasks in groups' projects.
        PROJECT_ID	int		NOT NULL,
	GROUP_ID	int		NOT NULL,
	DIVISION_ID	int		NOT NULL,
	ENTERPRISE_ID	int		NOT NULL,
	TASK_ID		int		NOT NULL,
	DESCRIPTION	char(88)	NOT NULL,	-- A description of the task.
	DESCRIPTION2	char(255)	NULL
)



create table PERSONNAL_INFO  (				-- The list of personnal.
	PERSONNAL_ID	int		PRIMARY KEY,	-- The field PERSONNAL_ID is unique.
	LAST_NAME	char(32)	NOT NULL,
	FIRST_NAME	char(22)	NULL,
	MIDDLE_NAME	char(12)	NULL,
	OTHER_NAME	char(12)	NULL,
	TITLE_1		char(22)	NULL,
	TITLE_2		char(22)	NULL,
	DESCRIPTION	char(88)	NULL
)

create table PERSONNAL_ADDRESS  (
	PERSONNAL_ID	int		NOT NULL,	-- A person may have more than one address.
	SEQUENCE	int		NOT NULL,
	STREET		char(32)	NULL,
	STREET2		char(22)	NULL,
	CITY		char(22)	NULL,
	STATE		char(22)	NULL,
	COUNTRY		char(22)	NULL,
	ZIP		char(22)	NULL,
	PHONE		char(22)	NULL
)

create table PERSONNAL_SKILLS  (			-- The list of skills a person possesses.
	PERSONNAL_ID	int		NOT NULL,
	SKILL_ID	int		NOT NULL,
	EXPERIENCE	int		NULL
)

create table SKILL_INFO  (				-- The list of skills and their descriptions.
	SKILL_ID	int		PRIMARY KEY,	-- The field SKILL_ID is unique.
	DESCRIPTION	char(88)	NOT NULL,
	DESCRIPTION2	char(255)	NULL
)

go


--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

insert into ENTERPRISE_INFO  (ENTERPRISE_ID, DESCRIPTION, DESCRIPTION2)
values  (200, 'EMPLOYER X', 'This is a test enterprise entry.')

insert into ENTERPRISE_DIVISION_INFO  (DIVISION_ID, ENTERPRISE_ID, DESCRIPTION, DESCRIPTION2)
values  (1, 200, 'DIVISION Y', 'This is a test division in EMPLOYER X.')

insert into ENTERPRISE_DIVISION_INFO  (DIVISION_ID, ENTERPRISE_ID, DESCRIPTION, DESCRIPTION2)
values  (2, 200, 'DIVISION Z', 'This is a test division in EMPLOYER X.')

insert into ENTERPRISE_DIVISION_GROUP_INFO  (GROUP_ID, DIVISION_ID, ENTERPRISE_ID, DESCRIPTION, DESCRIPTION2)
values  (9000, 2, 200, 'GROUP 9000', 'This is a test group in DIVISION Z in EMPLOYER X.')



insert into GROUP_PROJECT_INFO  (PROJECT_ID, GROUP_ID, DIVISION_ID, ENTERPRISE_ID, DESCRIPTION, DESCRIPTION2)
values  (5555, 9000, 2, 200, 'PROJECT YUP', 'Project YUP is a test project for GROUP 9000 in DIVISION Z in EMPLOYER X.')

insert into GROUP_PROJECT_CREW  (PROJECT_ID, GROUP_ID, DIVISION_ID, ENTERPRISE_ID, PERSONNAL_ID, TASK_ID)
values  (5555, 9000, 2, 200, 20002, 30001)

insert into GROUP_PROJECT_CREW  (PROJECT_ID, GROUP_ID, DIVISION_ID, ENTERPRISE_ID, PERSONNAL_ID, TASK_ID)
values  (5555, 9000, 2, 200, 20003, 30001)

insert into GROUP_PROJECT_TASK_INFO  (PROJECT_ID, GROUP_ID, DIVISION_ID, ENTERPRISE_ID, TASK_ID, DESCRIPTION, DESCRIPTION2)
values  (5555, 9000, 2, 200, 30001, 'BUSY WORK ONE', 'Task BUSY WORK ONE is a test task in this test database.')

insert into GROUP_PROJECT_TASK_INFO  (PROJECT_ID, GROUP_ID, DIVISION_ID, ENTERPRISE_ID, TASK_ID, DESCRIPTION, DESCRIPTION2)
values  (5555, 9000, 2, 200, 30002, 'BUSY WORK TWO', 'Task BUSY WORK TWO is a test task in this test database.')

insert into GROUP_PROJECT_TASK_INFO  (PROJECT_ID, GROUP_ID, DIVISION_ID, ENTERPRISE_ID, TASK_ID, DESCRIPTION, DESCRIPTION2)
values  (5555, 9000, 2, 200, 30003, 'BUSY WORK THREE', 'Task BUSY WORK THREE is a test task in this test database.')



insert into PERSONNAL_INFO  (PERSONNAL_ID, LAST_NAME, FIRST_NAME, MIDDLE_NAME, TITLE_1, DESCRIPTION)
values  (20002, 'HUFFMAN', 'DANIEL', 'NORMAN', 'SOFTWARE ENGINEER', 'CONSULTANT')

insert into PERSONNAL_SKILLS  (PERSONNAL_ID, SKILL_ID, EXPERIENCE)
values  (20002, 22, 5)

insert into PERSONNAL_SKILLS  (PERSONNAL_ID, SKILL_ID, EXPERIENCE)
values  (20002, 32, 2)

insert into PERSONNAL_INFO  (PERSONNAL_ID, LAST_NAME, FIRST_NAME, TITLE_1, DESCRIPTION)
values  (20003, 'SMITH', 'WILL', 'ENTERTAINER', 'Men in Black')

insert into PERSONNAL_ADDRESS  (PERSONNAL_ID, SEQUENCE, STREET, CITY, STATE, COUNTRY, ZIP, PHONE)
values  (20003, 1, '1234 Ogothorp Street', 'Oakland', 'CA', 'USA', '92443', '412-555-8234')

insert into PERSONNAL_SKILLS  (PERSONNAL_ID, SKILL_ID, EXPERIENCE)
values  (20003, 44, 10)



insert into SKILL_INFO  (SKILL_ID, DESCRIPTION, DESCRIPTION2)
values  (22, 'C++', 'C++ programming.')

insert into SKILL_INFO  (SKILL_ID, DESCRIPTION, DESCRIPTION2)
values  (32, 'Java', 'Java programming.')

insert into SKILL_INFO  (SKILL_ID, DESCRIPTION, DESCRIPTION2)
values  (44, 'Acting', 'Performance art.')

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------

select * from PERSONNAL_INFO
go


select PERSONNAL_INFO.PERSONNAL_ID, PERSONNAL_INFO.FIRST_NAME, PERSONNAL_INFO.LAST_NAME,
SKILL_INFO.DESCRIPTION, SKILL_INFO.DESCRIPTION2
from PERSONNAL_INFO, PERSONNAL_SKILLS, SKILL_INFO
where PERSONNAL_INFO.PERSONNAL_ID = PERSONNAL_SKILLS.PERSONNAL_ID
and PERSONNAL_SKILLS.SKILL_ID = SKILL_INFO.SKILL_ID
and PERSONNAL_SKILLS.EXPERIENCE > 4
go

--------------------------------------------------------------------------------
--------------------------------------------------------------------------------


drop table ENTERPRISE_INFO, ENTERPRISE_DIVISION_INFO,
ENTERPRISE_DIVISION_GROUP_INFO, GROUP_PROJECT_INFO, GROUP_PROJECT_CREW, GROUP_PROJECT_TASK_INFO,
PERSONNAL_INFO, PERSONNAL_ADDRESS, PERSONNAL_SKILLS, SKILL_INFO
go


quit
!

exit 0
